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
    TrainControllerMoc* configureManual();
    TrainControllerMoc* configureAutomatic();

private slots:
    void testPullServiceBrake();
    void testPullEmergencyBrake();
    void testIncSetpointSpeed();
    void testChooseVcmdManual();
    void testChooseVcmdAutomatic();
    void testDecodeTrackCircuit();
    void testZeroAuthority();
    void testCalcPowerMax();
};

TrainControllerMoc* testSpeedRegulator::configureManual()
{
    //Set the mode to 1
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Set Kp and Ki to nonzero values
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    sr -> setKpAndKi(.5,.5);

    //Send track circuit data and release brake to get train moving
    TrainMoc *tm = tc -> getTrainModel();
    tm -> setServiceBrake(0);
    tm -> trackCircuit = 0x0002000000000032; //com speed = 32 km/hr => 19.8839 mi/hr, auth = 32 blocks

    return tc;

}

TrainControllerMoc* testSpeedRegulator::configureAutomatic()
{
    //Set the mode to 0
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(0);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Set Kp and Ki to nonzero values
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    sr -> setKpAndKi(.5,.5);

    //Send track circuit data and release brake to get train moving
    TrainMoc *tm = tc -> getTrainModel();
    tm -> setServiceBrake(0);
    tm -> trackCircuit = 0x0002000000000032; //com speed = 32 km/hr => 19.8839 mi/hr, auth = 32 blocks

    return tc;

}

void testSpeedRegulator::testPullServiceBrake()
{
    //Create a train controller object to test
    TrainControllerMoc *tc = configureManual();
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Give the train controller a default setpoint speed of 30 mi/hr
    sr -> incSetpointSpeed(30);

    QCOMPARE(tm -> getEmergencyBrake(), 0);
    QCOMPARE(tm -> getServiceBrake(), 0);

    //Ensure setpoint speed is 30
    QCOMPARE(sr -> getSetpointSpeed(),48.2802);

    //Ensure power is not 0
    QVERIFY(sr -> getPowerCmd() != 0);

    //Now pull the service brake and ensure power is 0 and setpoint speed is 0
    sr -> pullServiceBrake();

    //Ensure power command is 0
    QCOMPARE(sr -> getPowerCmd(),0);

    //Ensure the setpoint speed is 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Ensure that the service brake has been pulled in the train
    QCOMPARE(tm -> getServiceBrake(),1);

}

void testSpeedRegulator::testPullEmergencyBrake()
{
    //Create a train controller object to test
    TrainControllerMoc *tc = configureManual();
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Give the train controller a default setpoint speed of 30 mi/hr
    sr -> incSetpointSpeed(30);

    //Set the track circuit to have a commanded speed greater than 0
    tm -> trackCircuit = 0x0002000000000030;

    //Ensure setpoint speed is 30 mi/hr => 48.2802 km/hr
    QCOMPARE(sr -> getSetpointSpeed(),48.2802);

    //Ensure power is not 0
    QVERIFY(sr -> getPowerCmd() != 0);

    //Now pull the emergency brake and ensure power is 0 and setpoint speed is 0
    sr -> pullEmergencyBrake();

    //Ensure power command is 0
    QVERIFY(sr -> getPowerCmd() == 0);

    //Ensure the setpoint speed is 0
    QVERIFY(sr -> getSetpointSpeed() == 0);

    //Ensure that the service brake has been pulled in the train
    QVERIFY(tm -> getEmergencyBrake() == 1);
}

void testSpeedRegulator::testIncSetpointSpeed()
{
    //Create a train controller object to test
    TrainControllerMoc *tc = configureManual();
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();

    //Ensure the speed starts out as 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Increment the speed and ensure that the speed increases
    double setpointSpeed = 0;

    //Attempt to decrement the speed and ensure that it does not go below 0
    sr -> incSetpointSpeed(-2);

    //Ensure the setpoint speed is still 0
    QCOMPARE(sr -> getSetpointSpeed(), 0);

    //Ensure that the speed increases when the joystick is pushed (until the max)
    while(setpointSpeed < 67.59228)
    {
        //Increase the setpoint speed
        sr -> incSetpointSpeed(2);
        setpointSpeed += 2*1.60934;

        //Ensure the setpoint speed updates
        QCOMPARE(sr -> getSetpointSpeed(), setpointSpeed);
    }

    //Increase the setpoint speed to ensure that the speed does not increase the max
    for(int i = 0; i<10; i++)
    {
        sr -> incSetpointSpeed(2);
        QCOMPARE(sr -> getSetpointSpeed(),67.59228);
    }
}

void testSpeedRegulator::testChooseVcmdManual()
{
    //Create a train controller object to test
    TrainControllerMoc *tc = configureManual();
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Set track circuit
    tm -> trackCircuit = 0x0003200000000032; //com speed = 50 km/hr => 31.0686 mi/hr, authority is 32 blocks

    //Ensure the setpoint speed is 0
    QCOMPARE(sr -> getSetpointSpeed(),0);

    //Ensure that Vcmd is 0
    QCOMPARE(sr -> getVcmd(), 0);

    //Increase the setpoint speed so it is still below commanded speed
    //using 30 mi/hr => 48.2802 km/hr
    sr -> incSetpointSpeed(30);

    //Ensure the setpoint speed is 30 mi/hr => 48.2802 km/hr
    QCOMPARE(sr -> getSetpointSpeed(),48.2802);

    //Ensure that Vcmd is 30 mi/hr => 48.2802 km/hr
    QCOMPARE(sr -> getVcmd(), 48.2802);

    //Increase the setpoint speed so it is equal to commanded speed
    sr -> incSetpointSpeed(1.0686);

    //Ensure the setpoint speed is 31.0606 mi/hr => 50 km/hr (the commanded speed)
    QVERIFY(sr -> getSetpointSpeed() > 49.99 && sr -> getSetpointSpeed() < 50.01);

    //Ensure that Vcmd is 31.0686 mi/hr => 50 km/hr
    QVERIFY(sr -> getVcmd() > 49.99 && sr -> getVcmd() < 50.01);

    //Increase the setpoint speed so it is above the commanded speed
    //using 31.0686 mi/hr => 53.2188 km/hr
    sr -> incSetpointSpeed(2);

    //Ensure the setpoint speed is 31.0686 mi/hr => 53.2188 km/hr
    QVERIFY(sr -> getSetpointSpeed() < 53.22 && sr -> getSetpointSpeed() > 53.20);

    //Ensure that Vcmd is 50 km/hr
    QCOMPARE(sr -> getVcmd(), 50);

}

void testSpeedRegulator::testChooseVcmdAutomatic()
{
    //Create a train controller object to test
    TrainControllerMoc *tc = configureAutomatic();
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Set track circuit
    tm -> trackCircuit = 0x0003200000000032; //com speed = 50 km/hr => 31.0686 mi/hr, authority is 32 blocks
    QVERIFY(sr -> getCommandedSpeed() == 50);
    QVERIFY(sr -> getAuthority() == 50);

    //Ensure the setpoint speed is 0
    QCOMPARE(sr -> getSetpointSpeed(),0);

    //Ensure that Vcmd is th commanded speed, which is 50 km/hr
    QCOMPARE(sr -> getVcmd(), 50);

    //Increase the setpoint speed so it is still below commanded speed
    //using 30 mi/hr => 48.2802 km/hr
    sr -> incSetpointSpeed(30);

    //Ensure the setpoint speed is 30 mi/hr => 48.2802 km/hr
    QCOMPARE(sr -> getSetpointSpeed(),48.2802);

    //Ensure that Vcmd is 50 km/hr
    QCOMPARE(sr -> getVcmd(), 50);

    //Increase the setpoint speed so it is equal to commanded speed
    sr -> incSetpointSpeed(1.0686);

    //Ensure the setpoint speed is 31.0606 mi/hr => 50 km/hr (the commanded speed)
    QVERIFY(sr -> getSetpointSpeed() > 49.99 && sr -> getSetpointSpeed() < 50.01);

    //Ensure that Vcmd is 31.0686 mi/hr => 50 km/hr
    QVERIFY(sr -> getVcmd() == 50);

    //Increase the setpoint speed so it is above the commanded speed
    //using 31.0686 mi/hr => 53.2188 km/hr
    sr -> incSetpointSpeed(2);

    //Ensure the setpoint speed is 31.0686 mi/hr => 53.2188 km/hr
    QVERIFY(sr -> getSetpointSpeed() < 53.22 && sr -> getSetpointSpeed() > 53.20);

    //Ensure that Vcmd is 50 km/hr
    QCOMPARE(sr -> getVcmd(), 50);

}

void testSpeedRegulator::testDecodeTrackCircuit()
{
    //Create a train controller object to test
    TrainControllerMoc *tc = configureManual();
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Give the track circuit different values and ensure that the decoder reads them correctly
    tm -> trackCircuit = 0x0002000000000032;
    QCOMPARE(sr -> getCommandedSpeed(), 32);
    QCOMPARE(sr -> getAuthority(), 50);

    tm -> trackCircuit = 0x0004500000000002;
    QCOMPARE(sr -> getCommandedSpeed(), 69);
    QCOMPARE(sr -> getAuthority(), 2);
}

void testSpeedRegulator::testZeroAuthority()
{
    //Create a train controller object to test
    TrainControllerMoc *tc = configureManual();
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Give the train a nonzero speed to get it moving
    //using 30 mi/hr => 48.2802 km/hr
    sr -> incSetpointSpeed(30);
    QCOMPARE(sr -> getSetpointSpeed(),48.2802);
    QVERIFY(sr -> getPowerCmd() != 0);

    //Give the track circuit an authority value of 0 and ensure service brake has been pulled
    tm -> trackCircuit = 0x0002000000000000;
    QCOMPARE(sr -> getAuthority(),0);
    QCOMPARE(sr -> getSetpointSpeed(),48.2802);
    QVERIFY(sr -> getPowerCmd() == 0);
    QCOMPARE(tm -> getServiceBrake(),1);
}

void testSpeedRegulator::testCalcPowerMax()
{
    //Create a train controller object to test
    TrainControllerMoc *tc = configureManual();
    SpeedRegulatorMoc *sr = tc -> getSpeedRegulator();
    TrainMoc *tm = tc -> getTrainModel();

    //Set track circuit
    tm -> trackCircuit = 0x0003200000000032; //com speed = 50 km/hr => 31.0686 mi/hr, authority is 32 blocks
    QVERIFY(sr -> getCommandedSpeed() == 50);
    QVERIFY(sr -> getAuthority() == 50);

    //Give the train a setpoint speed of 31.0686 mi/hr => 50 km/hr
    sr -> incSetpointSpeed(31.0686);
    QVERIFY(sr -> getSetpointSpeed() > 49.99 && sr -> getSetpointSpeed() < 50.01);

    //Ensure that the power command never goes above the max value of 120000 W
    for(int i = 0; i < 100; i++)
    {
        QVERIFY(sr -> getPowerCmd() <= 120000 && sr -> getPowerCmd() >= -120000);
    }
}

QTEST_APPLESS_MAIN(testSpeedRegulator)

#include "tst_testspeedregulator.moc"
