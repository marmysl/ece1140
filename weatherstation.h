#pragma once

#include <QObject>
#include <QDateTime>

class WeatherStation : public QObject
{
    Q_OBJECT

public:
    float tempCelcius;
    QTime lastUpdate;

    static float getTempCForTime( const QDateTime &time );

    explicit WeatherStation(QObject *parent = nullptr);

    float getTempFheit();
    bool isBelowFreezing();

    std::string getTempFString();
    std::string getTempCString();

public slots:
    void onTimeUpdate( const QDateTime &newTime, qint64 delta );

signals:
    void tempChanged();
};

extern WeatherStation weather;
