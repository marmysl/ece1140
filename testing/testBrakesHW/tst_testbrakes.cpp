#include <QtTest>
#include "TrainModel/Train.h"
#include "HWTrainController/TrainController.h"

class testBrakes : public QObject
{
    Q_OBJECT

public:
    testBrakes();
    ~testBrakes();

private slots:
    void pullServiceBrakes();

};

testBrakes::testBrakes()
{

}

testBrakes::~testBrakes()
{

}

void testBrakes::pullServiceBrakes()
{

}

QTEST_APPLESS_MAIN(testBrakes)

#include "tst_testbrakes.moc"
