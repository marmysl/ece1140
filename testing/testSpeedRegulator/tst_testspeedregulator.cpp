#include <QtTest>
#include <QObject>

#include "../mocs/TrainMoc.h"
#include "../mocs/TrainControllerMoc.h"
#include "../mocs/SpeedRegulatorMoc.h"
#include "../mocs/BeaconDecoderMoc.h"
#include "../mocs/CTCModeMoc.h"

#include <iostream>
#include <string>

class testSpeedRegulator : public QObject
{
    Q_OBJECT

public:

private slots:
    void testPullServiceBrake();
    void testPullEmergencyBrake();
    void testIncSetpointSpeed();
    void testChooseVcmd();
};

void testSpeedRegulator::testPullServiceBrake()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Retrieve object pointers from train controller
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Give the train controller a default setpoint speed of 30 mi/hr
    sr -> incSetpointSpeed(30);

    //Make the commanded speed and authority greater than 0 so the train can move
    tm -> sendTrackCircuit(); //authority is 50 and commanded speed is 40

    //Simulate incoming data to ensure the power command is not 0
    tc -> receiveData("00000044.4455.55000000");

    //Ensure setpoint speed is 30
    QCOMPARE(sr -> getSetpointSpeed(),30);

    //Ensure power is not 0
    QVERIFY(sr -> getPowerCmd() != 0);

    //Now pull the service brake and ensure power is 0 and setpoint speed is 0
    tc -> receiveData("00000044.4455.55001000");

    //Ensure power command is 0
    QCOMPARE(sr -> getPowerCmd(),0);

    //Ensure the setpoint speed is 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Ensure that the service brake has been pulled in the train
    QCOMPARE(tm -> getServiceBrake(),1);

}

void testSpeedRegulator::testPullEmergencyBrake()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Retrieve object pointers from train controller
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Give the train controller a default setpoint speed of 30 mi/hr
    sr -> incSetpointSpeed(30);

    //Simulate incoming data to ensure the power command is not 0
    tc -> receiveData("00000044.4455.55000000");

    //Ensure setpoint speed is 30
    QCOMPARE(sr -> getSetpointSpeed(),30);

    //Ensure power is not 0
    QVERIFY(sr -> getPowerCmd() != 0);

    //Now pull the emergency brake and ensure power is 0 and setpoint speed is 0
    tc -> receiveData("00000044.4455.55000100");

    //Ensure power command is 0
    QVERIFY(sr -> getPowerCmd() == 0);

    //Ensure the setpoint speed is 0
    QVERIFY(sr -> getSetpointSpeed() == 0);

    //Ensure the proper values are being output to the Arduino
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(37,1),"1");

    //Ensure that the service brake has been pulled in the train
    QVERIFY(tm -> getEmergencyBrake() == 1);
}

void testSpeedRegulator::testIncSetpointSpeed()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Retrieve object pointers from train controller
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();

    //Ensure the speed starts out as 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Increment the speed and ensure that the speed increases
    double setpointSpeed = 0;

    //Attempt to decrement the speed and ensure that it does not go below 0
    tc -> receiveData("00000044.4455.55010000");

    //Ensure the setpoint speed is still 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Ensure that the speed increases when the joystick is pushed (until the max)
    while(setpointSpeed <= 41)
    {
        //Increase the setpoint speed
        tc -> receiveData("00000044.4455.551000000");
        setpointSpeed += 2;

        //Ensure the setpoint speed updates
        QCOMPARE(sr -> getSetpointSpeed(), setpointSpeed);
    }

    //Increase the setpoint speed to ensure that the speed does not increase the max
    for(int i = 0; i<10; i++)
    {
        tc -> receiveData("00000044.4455.551000000");

        QVERIFY(sr -> getSetpointSpeed() <= 43);
    }
}

void testSpeedRegulator::testChooseVcmd()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Retrieve object pointers from train controller
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Set the track circuit so that authority = 50 and commanded speed = 40
    tm -> trackCircuit = 0x0000002800000032;

    //Ensure the setpoint speed is 0
    QCOMPARE(sr -> getSetpointSpeed(),0);

    //Ensure that Vcmd is 0
    QCOMPARE(sr -> getVcmd(), 0);

    //Increase the setpoint speed so it is still below commanded speed
    sr -> incSetpointSpeed(30);

    //Ensure the setpoint speed is 30
    QCOMPARE(sr -> getSetpointSpeed(),30);

    //Ensure that Vcmd is 30
    QCOMPARE(sr -> getVcmd(), 30);

    //Increase the setpoint speed so it is equal to commanded speed
    sr -> incSetpointSpeed(10);

    //Ensure the setpoint speed is 40
    QCOMPARE(sr -> getSetpointSpeed(),40);

    //Ensure that Vcmd is 40
    QCOMPARE(sr -> getVcmd(), 40);

    //Increase the setpoint speed so it is above the commanded speed
    sr -> incSetpointSpeed(2);

    //Ensure the setpoint speed is 42
    QCOMPARE(sr -> getSetpointSpeed(), 42);

    //Ensure that Vcmd is 40
    QCOMPARE(sr -> getVcmd(), 40);

}


QTEST_APPLESS_MAIN(testSpeedRegulator)

#include "tst_testspeedregulator.moc"
