#pragma once

#include <QObject>
#include <QDateTime>

class WeatherStation : public QObject
{
    Q_OBJECT

public:
    float tempCelcius;
    bool forcingTemp;
    QTime lastUpdate;

    static float getTempCForTime( const QDateTime &time );
    static float convertFtoC( float tempF );
    static float convertCtoF( float tempC );

    explicit WeatherStation(QObject *parent = nullptr);

    void forceTempF( float tempF );
    void stopForcingTemp();

    float getTempFheit();
    bool isBelowFreezing();

    std::string getTempFString();
    std::string getTempCString();

public slots:
    void onTimeUpdate( const QDateTime &newTime, qint64 delta );

signals:
    void tempChanged();
};

extern WeatherStation *weather;
