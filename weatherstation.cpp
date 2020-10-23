#include "weatherstation.h"
#include <QDateTime>
#include <cmath>

const float TAU = 6.28318530717958647692;

WeatherStation weather;

float WeatherStation::getTempCForTime( const QDateTime &time )
{
    QDate yearStartDate(time.date().year(), 1, 1);
    QDateTime yearStart = yearStartDate.startOfDay();

    float daysIntoYear = yearStart.secsTo(time) / 86400.0f; // 60s > 60m > 24h

    float annualVar = 11 - (12 * cosf(TAU*(daysIntoYear - 15) / 365.25f));
    float dailyVar = -5 * cosf(TAU * (daysIntoYear - 0.125f));

    return annualVar + dailyVar;
}

WeatherStation::WeatherStation(QObject *parent) : QObject(parent)
{
    tempCelcius = 12.0f; // avg october temp
}

float WeatherStation::getTempFheit()
{
    return (tempCelcius * 1.8f) + 32;
}

bool WeatherStation::isBelowFreezing()
{
    return tempCelcius < 0;
}

std::string WeatherStation::getTempFString()
{
    char buf[10];
    sprintf(buf, "%.1f F", getTempFheit());
    return std::string(buf);
}

std::string WeatherStation::getTempCString()
{
    char buf[10];
    sprintf(buf, "%.1f C", tempCelcius);
    return std::string(buf);
}

void WeatherStation::onTimeUpdate( const QDateTime &newTime, qint64 delta )
{
    tempCelcius = getTempCForTime(newTime);
    tempChanged();
}
