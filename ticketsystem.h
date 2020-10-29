#pragma once

#include "TrackModel/tracklayout.hpp"

#include <QObject>
#include <QDateTime>

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

public:
    std::vector<Passenger> soldTickets;

    explicit TicketSystem(QObject *parent = nullptr);

    void clearSales();
    void sellTickets( Route *route, Station *station, QDateTime time, int count );

signals:
    void ticketsChanged();
};

extern TicketSystem *ticketSystem;
