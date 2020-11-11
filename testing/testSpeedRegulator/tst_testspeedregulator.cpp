#include <QtTest>
#include <QObject>

#include "../mocs/Train.h"
#include "../mocs/TrainControllerMoc.h"
#include "../mocs/SpeedRegulator.h"
#include "../mocs/BeaconDecoder.h"

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
    void testChooseVcmdManual();
    void testChooseVcmdAutomatic();
    void testDecodeTrackCircuit();
    void testKpAndKi();
};

void testSpeedRegulator::testPullServiceBrake()
{
    //Tests that when the service brake is pulled the power command goes to 0 and the setpoint speed goes to 0
    TrainControllerMoc* tc = new TrainControllerMoc(1);

    //Retrieve object pointers from train controller
    SpeedRegulator *sr = tc -> getSpeedRegulator();
    Train *tm = tc -> getTrainModel();

    //Make the commanded speed and authority greater than 0 so the train can move
    tm -> trackCircuit = 0x0002800000032000; //authority is 50 and commanded speed is 40

    //Ensure pullServiceBrake is called upon creation of speed regulator object
    QCOMPARE(tm -> getServiceBrake(), 1);

    //Ensure interface is updated with service brake information
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(36,1), "1");

    //Release service brake so driver can increase setpoint speed
    tc -> receiveData("00000044.4455.5500000010");

    //Ensure interface is updated with service brake information
    data = tc -> writeData();
    QCOMPARE(data.substr(36,1), "0");

    //Give the train controller a default setpoint speed of 30 mi/hr
    sr -> incSetpointSpeed(30);

    //Ensure setpoint speed is 30
    QCOMPARE(sr -> getSetpointSpeed(),30);

    //Ensure power is not 0
    QVERIFY(sr -> getPowerCmd() != 0);

    //Now pull the service brake and ensure power is 0 and setpoint speed is 0
    tc -> receiveData("00000044.4455.5500100000");

    //Ensure power command is 0
    QCOMPARE(sr -> getPowerCmd(),0);

    //Ensure the setpoint speed is 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Ensure that the service brake has been pulled in the train
    QCOMPARE(tm -> getServiceBrake(),1);

    //Ensure interface is updated with service brake information
    data = tc -> writeData();
    QCOMPARE(data.substr(36,1), "1");


}

void testSpeedRegulator::testPullEmergencyBrake()
{
    //Tests that when the emergency brake is pulled the power command goes to 0 and the setpoint speed goes to 0
    TrainControllerMoc* tc = new TrainControllerMoc(1);

    //Retrieve object pointers from train controller
    SpeedRegulator *sr = tc -> getSpeedRegulator();
    Train *tm = tc -> getTrainModel();

    //Make the commanded speed and authority greater than 0 so the train can move
    tm -> trackCircuit = 0x0002800000032000; //authority is 50 and commanded speed is 40

    //Ensure pull emegency brake is 0 upon initialization
    QCOMPARE(tm -> getEmergencyBrake(), 0);

    //Ensure interface is updated with service brake information
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(37,1), "0");

    //Release service brake so driver can increase setpoint speed
    tc -> receiveData("00000044.4455.5500000010");

    //Ensure interface is updated with emergency brake information
    data = tc -> writeData();
    QCOMPARE(data.substr(37,1), "0");

    //Give the train controller a default setpoint speed of 30 mi/hr
    sr -> incSetpointSpeed(30);

    //Ensure setpoint speed is 30
    QCOMPARE(sr -> getSetpointSpeed(),30);

    //Ensure power is not 0
    QVERIFY(sr -> getPowerCmd() != 0);

    //Now pull the emergency brake and ensure power is 0 and setpoint speed is 0
    tc -> receiveData("00000044.4455.5500010000");

    //Ensure power command is 0
    QCOMPARE(sr -> getPowerCmd(),0);

    //Ensure the setpoint speed is 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Ensure that the emergency brake has been pulled in the train
    QCOMPARE(tm -> getEmergencyBrake(),1);

    //Ensure interface is updated with emergency brake information
    data = tc -> writeData();
    QCOMPARE(data.substr(37,1), "1");
}

void testSpeedRegulator::testIncSetpointSpeed()
{
    //Creates a train controller object to test
    TrainControllerMoc* tc = new TrainControllerMoc(1);

    //Retrieve object pointers from train controller
    SpeedRegulator *sr = tc -> getSpeedRegulator();
    Train *tm = tc -> getTrainModel();

    //Make the commanded speed and authority greater than 0 so the train can move
    tm -> trackCircuit = 0x0002800000032000; //authority is 50 and commanded speed is 40

    //Release service brake so driver can increase setpoint speed
    tc -> receiveData("00000044.4455.5500000011");

    //Ensure the speed starts out as 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Increment the speed and ensure that the speed increases
    double setpointSpeed = 0;

    //Attempt to decrement the speed and ensure that it does not go below 0
    tc -> receiveData("00000044.4455.5501000001");

    //Ensure the setpoint speed is still 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Ensure that the speed increases when the joystick is pushed (until the max)
    while(setpointSpeed <= 35)
    {
        //Increase the setpoint speed
        tc -> receiveData("00000044.4455.55100000001");
        setpointSpeed += 5;

        //Ensure the setpoint speed updates
        QCOMPARE(sr -> getSetpointSpeed(), setpointSpeed);
    }

    //Increase the setpoint speed to ensure that the speed does not increase the max
    for(int i = 0; i<10; i++)
    {
        tc -> receiveData("00000044.4455.55100000001");

        QVERIFY(sr -> getSetpointSpeed() <= 43);
    }
}

void testSpeedRegulator::testChooseVcmdManual()
{
    //Creates a train controller object to test
    TrainControllerMoc* tc = new TrainControllerMoc(1);

    //Retrieve object pointers from train controller
    SpeedRegulator *sr = tc -> getSpeedRegulator();
    Train *tm = tc -> getTrainModel();

    //Release service brake so driver can increase setpoint speed
    tc -> receiveData("00000044.4455.5500000010");

    //Set the track circuit so that authority = 50 and commanded speed = 40
    tm -> trackCircuit = 0x0002800000032000;

    //Set the mode to manual
    tc -> setMode(1);

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

    std::cout << "Commanded Speed: " << sr -> getCommandedSpeed() << std::endl;

    //Ensure that Vcmd is 40
    QCOMPARE(sr -> getVcmd(), 40);

}

void testSpeedRegulator::testChooseVcmdAutomatic()
{
    //Creates a train controller object to test
    TrainControllerMoc* tc = new TrainControllerMoc(0);

    //Retrieve object pointers from train controller
    SpeedRegulator *sr = tc -> getSpeedRegulator();
    Train *tm = tc -> getTrainModel();

    //Set the track circuit so that authority = 50 and commanded speed = 40
    tm -> trackCircuit = 0x0002800000032000;

    //Ensure service brake is on upon instantiation
    QCOMPARE(tm -> getServiceBrake(), 1);

    //Release the service brake
    tc -> receiveData("00000000300.0400.00000100");

    //Ensure the brake is released
    QCOMPARE(tm -> getServiceBrake(), 0);

    //Ensure the setpoint speed is 0
    QCOMPARE(sr -> getSetpointSpeed(),0);

    //Call the choose Vcmd method
    sr -> chooseVcmd();

    //Ensure that Vcmd is 40
    QCOMPARE(sr -> getVcmd(), 40);

    //Increase the setpoint speed so it is still below commanded speed
    sr -> incSetpointSpeed(30);

    //Ensure the setpoint speed is 30
    QCOMPARE(sr -> getSetpointSpeed(),30);

    //Call the choose Vcmd method
    sr -> chooseVcmd();

    //Ensure that Vcmd is 40
    QCOMPARE(sr -> getVcmd(), 40);

    //Increase the setpoint speed so it is equal to commanded speed
    sr -> incSetpointSpeed(10);

    //Ensure the setpoint speed is 40
    QCOMPARE(sr -> getSetpointSpeed(),40);

    //Call the choose Vcmd method
    sr -> chooseVcmd();

    //Ensure that Vcmd is 40
    QCOMPARE(sr -> getVcmd(), 40);

    //Increase the setpoint speed so it is above the commanded speed
    sr -> incSetpointSpeed(2);

    //Ensure the setpoint speed is 42
    QCOMPARE(sr -> getSetpointSpeed(), 42);

    //Call the choose Vcmd method
    sr -> chooseVcmd();

    //Ensure that Vcmd is 40
    QCOMPARE(sr -> getVcmd(), 40);

}

void testSpeedRegulator::testDecodeTrackCircuit()
{
    //Creates a train controller object to test
    TrainControllerMoc* tc = new TrainControllerMoc(0);

    //Retrieve object pointers from train controller
    SpeedRegulator *sr = tc -> getSpeedRegulator();
    Train *tm = tc -> getTrainModel();

    //Set the track circuit so that authority = 50 and commanded speed = 40
    tm -> trackCircuit = 0x0002800000032000;

    //Ensure that the track circuit is decoded correctly
    QCOMPARE(sr -> getCommandedSpeed(), 40);
    QCOMPARE(sr -> getAuthority(), 50);

    //Set the track circuit so that authority = 50 and commanded speed = 40
    tm -> trackCircuit = 0x0000f00000009000;

    //Ensure that the track circuit is decoded correctly
    QCOMPARE(sr -> getCommandedSpeed(), 15);
    QCOMPARE(sr -> getAuthority(), 9);

}

void testSpeedRegulator::testKpAndKi()
{
    //Creates a train controller object to test
    TrainControllerMoc* tc = new TrainControllerMoc(0);

    //Retrieve object pointers from train controller
    SpeedRegulator *sr = tc -> getSpeedRegulator();

    //Receive sample data from arduino
    tc -> receiveData("000000300.0400.000000000");

    //Ensure the correct values of Kp and Ki have been set
    QCOMPARE(sr -> getKp(), 300000);
    QCOMPARE(sr -> getKi(), 400000);

    //Receive sample data from arduino
    tc -> receiveData("00000055.5544.4400000000");

    //Ensure the correct values of Kp and Ki have been set
    QCOMPARE(sr -> getKp(), 55550);
    QCOMPARE(sr -> getKi(), 44440);

}

QTEST_APPLESS_MAIN(testSpeedRegulator)

#include "tst_testspeedregulator.moc"
