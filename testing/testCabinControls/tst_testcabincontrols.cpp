#include <QtTest>
#include <QObject>

#include "../mocs/TrainMoc.h"
#include "../mocs/TrainControllerMoc.h"
#include "../mocs/SpeedRegulatorMoc.h"
#include "../mocs/BeaconDecoderMoc.h"
#include "../mocs/CTCModeMoc.h"

#include <iostream>
#include <string>


class testCabinControls : public QObject
{
    Q_OBJECT

public:

private slots:
    void testCabinLights();
    void testCabinAc();
    void testCabinHeat();
    void testCabinAdvertisements();
    void testCabinAnnouncements();
    void testCabinDoors();
    void testHeadlights();


};

void testCabinControls::testCabinLights()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Obtain trainModel object from train controller
    TrainMoc *tm = tc -> getTrainModel();

    //Ensure the cabin lights are initially off
    QCOMPARE(tm -> getCabinLights(), 0);

    //Provides incoming simulated serial port data to turn the lights on
    tc -> receiveData("10000044.4455.55000000");
    QCOMPARE(tm -> getCabinLights(), 1);

    //Ensure the proper values are being output to the Arduino
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(0,1),"1");

    //Provides incoming simulated serial port data to turn the lights off
    tc -> receiveData("00000044.4455.55000000");
    QCOMPARE(tm -> getCabinLights(), 0);

    //Ensure the proper values are being output to the Arduino
    data = tc -> writeData();
    QCOMPARE(data.substr(0,1),"0");
}

void testCabinControls::testCabinAc()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Obtain trainModel object from train controller
    TrainMoc *tm = tc -> getTrainModel();

    //Ensure the ac is initially off
    QCOMPARE(tm -> getAC(), 0);

    //Provides incoming simulated serial port data to turn the ac on
    tc -> receiveData("01000044.4455.55000000");
    QCOMPARE(tm -> getAC(), 1);

    //Ensure the proper values are being output to the Arduino
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(1,1),"1");

    //Provides incoming simulated serial port data to turn the ac off
    tc -> receiveData("00000044.4455.55000000");
    QCOMPARE(tm -> getAC(), 0);

    //Ensure the proper values are being output to the Arduino
    data = tc -> writeData();
    QCOMPARE(data.substr(1,1),"0");
}

void testCabinControls::testCabinHeat()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Obtain trainModel object from train controller
    TrainMoc *tm = tc -> getTrainModel();

    //Ensure the heat is initially off
    QCOMPARE(tm -> getHeater(), 0);

    //Provides incoming simulated serial port data to turn the heat on
    tc -> receiveData("00100044.4455.55000000");
    QCOMPARE(tm -> getHeater(), 1);

    //Ensure the proper values are being output to the Arduino
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(2,1),"1");

    //Provides incoming simulated serial port data to turn the heat off
    tc -> receiveData("00000044.4455.55000000");
    QCOMPARE(tm -> getHeadlights(), 0);

    //Ensure the proper values are being output to the Arduino
    data = tc -> writeData();
    QCOMPARE(data.substr(2,1),"0");
}

void testCabinControls::testCabinAdvertisements()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Obtain trainModel object from train controller
    TrainMoc *tm = tc -> getTrainModel();

    //Ensure the ads are initially off
    QCOMPARE(tm -> getAdvertisements(), 0);

    //Provides incoming simulated serial port data to turn the ads on
    tc -> receiveData("00001044.4455.55000000");
    QCOMPARE(tm -> getAdvertisements(), 1);

    //Ensure the proper values are being output to the Arduino
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(4,1),"1");

    //Provides incoming simulated serial port data to turn the ads off
    tc -> receiveData("00000044.4455.55000000");
    QCOMPARE(tm -> getAdvertisements(), 0);

    //Ensure the proper values are being output to the Arduino
    data = tc -> writeData();
    QCOMPARE(data.substr(4,1),"0");
}

void testCabinControls::testCabinAnnouncements()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Obtain trainModel object from train controller
    TrainMoc *tm = tc -> getTrainModel();

    //Ensure the announcements are initially off
    QCOMPARE(tm -> getAnnouncements(), 0);

    //Provides incoming simulated serial port data to turn the announcements on
    tc -> receiveData("00000144.4455.55000000");
    QCOMPARE(tm -> getAnnouncements(), 1);

    //Ensure the proper values are being output to the Arduino
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(5,1),"1");

    //Provides incoming simulated serial port data to turn the announcements off
    tc -> receiveData("00000044.4455.55000000");
    QCOMPARE(tm -> getAnnouncements(), 0);

    //Ensure the proper values are being output to the Arduino
    data = tc -> writeData();
    QCOMPARE(data.substr(5,1),"0");
}

void testCabinControls::testCabinDoors()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Obtain trainModel object from train controller
    TrainMoc *tm = tc -> getTrainModel();

    //Ensure the headlights are initially closed
    QCOMPARE(tm -> getLeftDoorStatus(), 0);

    //Provides incoming simulated serial port data to open
    tc -> receiveData("00010044.4455.55000001");
    QCOMPARE(tm -> getLeftDoorStatus(), 1);

    //Ensure the proper values are being output to the Arduino
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(44,1),"1");

    //Provides incoming simulated serial port data to close the doors
    tc -> receiveData("00000044.4455.55000000");
    QCOMPARE(tm -> getLeftDoorStatus(), 0);

    //Ensure the proper values are being output to the Arduino
    data = tc -> writeData();
    QCOMPARE(data.substr(44,1),"0");
}

void testCabinControls::testHeadlights()
{
    //Create a CTC Mode object to set the mode of the train controller
    CTCModeMoc* modeInit = new CTCModeMoc();
    modeInit -> setMode(1);

    //Create a train controller object to test
    TrainControllerMoc *tc = new TrainControllerMoc(modeInit, 3, "GreenLine");

    //Obtain trainModel object from train controller
    TrainMoc *tm = tc -> getTrainModel();

    //Ensure the headlights are initially off
    QCOMPARE(tm -> getHeadlights(), 0);

    //Provides incoming simulated serial port data to turn the lights on
    tc -> receiveData("00000044.4455.55000001");
    QCOMPARE(tm -> getHeadlights(), 1);

    //Ensure the proper values are being output to the Arduino
    std::string data = tc -> writeData();
    QCOMPARE(data.substr(44,1),"1");

    //Provides incoming simulated serial port data to turn the lights off
    tc -> receiveData("00000044.4455.55000000");
    QCOMPARE(tm -> getHeadlights(), 0);

    //Ensure the proper values are being output to the Arduino
    data = tc -> writeData();
    QCOMPARE(data.substr(44,1),"0");
}

QTEST_APPLESS_MAIN(testCabinControls)

#include "tst_testcabincontrols.moc"
