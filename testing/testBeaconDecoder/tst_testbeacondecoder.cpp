#include <QtTest>
#include <QObject>

#include "../mocs/TrainMoc.h"
#include "../mocs/TrainControllerMoc.h"
#include "../mocs/SpeedRegulatorMoc.h"
#include "../mocs/BeaconDecoderMoc.h"
#include "../mocs/CTCModeMoc.h"

#include <iostream>
#include <string>

using namespace TrackModel;

class testBeaconDecoder : public QObject
{
    Q_OBJECT

public:
    BeaconDecoderMoc* configure1();
    BeaconDecoderMoc* configure2();
    BeaconDecoderMoc* configure3();
    BeaconDecoderMoc* configure4();

private slots:
    void testExtractBeaconData1();
    void testExtractBeaconData2();
    void testExtractBeaconData3();
    void testExtractBeaconData4();
    void testGetAnnouncement1();
    void testGetAnnouncement2();
    void testGetAnnouncement3();
    void testGetAnnouncement4();
};

BeaconDecoderMoc* testBeaconDecoder::configure1()
{
   //Create a beacon data object
   BeaconData* beacon = new BeaconData();

   //Assign attributes to the beacon
   PlatformSide side(PS_RIGHT);
   beacon -> platformSide = side;
   beacon -> newLightState = 0;
   beacon -> stationUpcoming = 0;
   beacon -> stationHere = 1;
   beacon -> stationName = "Dormont";

   //Create a BeaconDecoder object
   BeaconDecoderMoc* bd = new BeaconDecoderMoc();
   bd -> setBeaconData(*beacon);

   return bd;
}
BeaconDecoderMoc* testBeaconDecoder::configure2()
{
    //Create a beacon data object
    BeaconData* beacon = new BeaconData();

    //Assign attributes to the beacon
    PlatformSide side(PS_LEFT);
    beacon -> platformSide = side;
    beacon -> newLightState = 0;
    beacon -> stationUpcoming = 1;
    beacon -> stationHere = 0;
    beacon -> stationName = "Poplar";

    //Create a BeaconDecoder object
    BeaconDecoderMoc* bd = new BeaconDecoderMoc();
    bd -> setBeaconData(*beacon);

    return bd;
}
BeaconDecoderMoc* testBeaconDecoder::configure3()
{
    //Create a beacon data object
    BeaconData* beacon = new BeaconData();

    //Assign attributes to the beacon
    PlatformSide side(PS_BOTH);
    beacon -> platformSide = side;
    beacon -> newLightState = 1;
    beacon -> stationUpcoming = 1;
    beacon -> stationHere = 0;
    beacon -> stationName = "Glenbury";

    //Create a BeaconDecoder object
    BeaconDecoderMoc* bd = new BeaconDecoderMoc();
    bd -> setBeaconData(*beacon);

    return bd;
}
BeaconDecoderMoc* testBeaconDecoder::configure4()
{
    //Create a beacon data object
    BeaconData* beacon = new BeaconData();

    //Assign attributes to the beacon
    PlatformSide side(PS_BOTH);
    beacon -> platformSide = side;
    beacon -> newLightState = 1;
    beacon -> stationUpcoming = 0;
    beacon -> stationHere = 0;
    beacon -> stationName = "Glenbury";

    //Create a BeaconDecoder object
    BeaconDecoderMoc* bd = new BeaconDecoderMoc();
    bd -> setBeaconData(*beacon);

    return bd;
}
void testBeaconDecoder::testExtractBeaconData1()
{
    //Create a beacon decoder object to test
    BeaconDecoderMoc* bd = configure1();

    //Ensure that each accessor reads in the right information
    QVERIFY(bd -> getNextStation() == "Dormont");
    QVERIFY(bd -> getStationCode() == "10000");
    QCOMPARE(bd -> getPlatformDoorsChar(),'\x01');
    QVERIFY(bd -> getTurnHeadlightsOn() == 0);
    QVERIFY(bd -> getStationUpcoming() == 0);
    QVERIFY(bd -> getStationHere() == 1);
    QVERIFY(bd -> getPlatformDoors() == "RIGHT");

}
void testBeaconDecoder::testExtractBeaconData2()
{
    //Create a beacon decoder object to test
    BeaconDecoderMoc* bd = configure2();

    //Ensure that each accessor reads in the right information
    QVERIFY(bd -> getNextStation() == "Poplar");
    QVERIFY(bd -> getStationCode() == "10010");
    QCOMPARE(bd -> getPlatformDoorsChar(), '\xff');
    QVERIFY(bd -> getTurnHeadlightsOn() == 0);
    QVERIFY(bd -> getStationUpcoming() == 1);
    QVERIFY(bd -> getStationHere() == 0);
    QVERIFY(bd -> getPlatformDoors() == "LEFT");

}
void testBeaconDecoder::testExtractBeaconData3()
{
    //Create a beacon decoder object to test
    BeaconDecoderMoc* bd = configure3();

    //Ensure that each accessor reads in the right information
    QVERIFY(bd -> getNextStation() == "Glenbury");
    QVERIFY(bd -> getStationCode() == "01111");
    QCOMPARE(bd -> getPlatformDoorsChar(), '\0');
    QVERIFY(bd -> getTurnHeadlightsOn() == 1);
    QVERIFY(bd -> getStationUpcoming() == 1);
    QVERIFY(bd -> getStationHere() == 0);
    QVERIFY(bd -> getPlatformDoors() == "BOTH");

}
void testBeaconDecoder::testExtractBeaconData4()
{
    //Create a beacon decoder object to test
    BeaconDecoderMoc* bd = configure4();

    //Ensure that each accessor reads in the right information (no beacon data)
    QVERIFY(bd -> getTurnHeadlightsOn() == 0);
    QVERIFY(bd -> getStationUpcoming() == 0);
    QVERIFY(bd -> getStationHere() == 0);

}

void testBeaconDecoder::testGetAnnouncement1()
{
    //Create a beacon decoder object to test
    BeaconDecoderMoc* bd = configure1();

    QVERIFY(bd -> getAnnouncement() == "The next station is Dormont. Please exit on your right.");
}
void testBeaconDecoder::testGetAnnouncement2()
{
    //Create a beacon decoder object to test
    BeaconDecoderMoc* bd = configure2();

    QVERIFY(bd -> getAnnouncement() == "The next station is Poplar. Please exit on your left.");
}
void testBeaconDecoder::testGetAnnouncement3()
{
    //Create a beacon decoder object to test
    BeaconDecoderMoc* bd = configure3();

    QVERIFY(bd -> getAnnouncement() == "The next station is Glenbury. Please exit on either side.");
}

void testBeaconDecoder::testGetAnnouncement4()
{
    //Create a beacon decoder object to test
    BeaconDecoderMoc* bd = configure4();

    QVERIFY(bd -> getAnnouncement() == "Thank you for choosing Port Authority.");
}


QTEST_APPLESS_MAIN(testBeaconDecoder)

#include "tst_testbeacondecoder.moc"
