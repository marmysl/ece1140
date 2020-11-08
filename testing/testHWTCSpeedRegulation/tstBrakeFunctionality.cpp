#include <QtTest>

// add necessary includes here

class ServiceBrakeFunctional : public QObject
{
    Q_OBJECT

public:
    ServiceBrakeFunctional();
    ~ServiceBrakeFunctional();

private slots:
    void test_case1();

};

ServiceBrakeFunctional::ServiceBrakeFunctional()
{

}

ServiceBrakeFunctional::~ServiceBrakeFunctional()
{

}

void ServiceBrakeFunctional::test_case1()
{

}

QTEST_APPLESS_MAIN(ServiceBrakeFunctional)

#include "tst_servicebrakefunctional.moc"
