#pragma once

#include "TrackModel/tracklayout.hpp"

#include <QObject>
#include <QDateTime>
#include <random>

using namespace TrackModel;

struct Passenger
{
    QString name;
    QDateTime purchaseTime;
    Route *route;
    Station *startStation;

    Passenger( QString name, QDateTime time, Route *rte, Station *station ) :
        name(name), purchaseTime(time), route(rte), startStation(station) {}

    static const char *firstNames[];
    static const int N_FIRSTNAME;
    static const char *lastNames[];
    static const int N_LASTNAME;

    static QString createName();
};

class TicketSystem : public QObject
{
    Q_OBJECT

private:
    const qint64 UPDATE_DELAY = 1200000;
    const int SOFT_PASSENGER_CAP = 220;

    qint64 msSinceUpdate = UPDATE_DELAY + 1;
    std::default_random_engine randEngine;
    std::normal_distribution<double> arrivalCurve = std::normal_distribution<double>(40.0, 5.0);

public:
    std::vector<Passenger> soldTickets;

    explicit TicketSystem(QObject *parent = nullptr);

    void clearSales();
    void sellOneTicket( Route *route, Station *station, QDateTime time );
    void sellTickets( Route *route, Station *station, QDateTime time, int count );

public slots:
    void onTimeUpdate(const QDateTime &newTime, qint64 deltaMs);

signals:
    void ticketsChanged();
};

extern TicketSystem *ticketSystem;
