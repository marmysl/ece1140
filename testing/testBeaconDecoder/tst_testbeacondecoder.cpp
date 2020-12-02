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


private slots:
    void test_case1();

};

BeaconDecoderMoc* testBeaconDecoder::configure1()
{
   BeaconDecoderMoc* bd = new BeaconDecoderMoc();
   return bd;
}
BeaconDecoderMoc* testBeaconDecoder::configure2()
{
    BeaconDecoderMoc* bd = new BeaconDecoderMoc();
    return bd;
}
BeaconDecoderMoc* testBeaconDecoder::configure3()
{
    BeaconDecoderMoc* bd = new BeaconDecoderMoc();
    return bd;
}
void testBeaconDecoder::test_case1()
{

}

QTEST_APPLESS_MAIN(testBeaconDecoder)

#include "tst_testbeacondecoder.moc"
