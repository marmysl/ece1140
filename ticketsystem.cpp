#include "ticketsystem.h"

TicketSystem *ticketSystem;

const char *Passenger::firstNames[]
{
    "Morgen", "Katy", "Chris", "Meara", "Maria", "Kirah", "Megan",
    "Cecil", "Carlos", "Abby", "Steve", "Janice",
    "Dana", "Earl", "Kevin", "Lauren", "Hiram",
    "Tamika", "Maureen", "Michelle", "John", "Diane",
    "Deb", "Josie", "Erika", "Pamela", "Marcus",
    "Leonard", "Louie", "Khoshekh", "Anna", "Melody",
    "Sheryl", "Fred", "Kaylin", "Felicity", "Clark",
    "Alma", "Rhianna", "David", "Kirsten", "Brian",
    "Angelica", "Charles", "Nina", "Trixie", "Gloria",
};

const int Passenger::N_FIRSTNAME = sizeof(Passenger::firstNames) / sizeof(char*);

const char *Passenger::lastNames[]
{
    "Benninghoff", "Fox", "Keach", "Murphy", "Mysliwiec", "Strandquist", "Toner",
    "Palmer", "Carlsberg", "Cardinal", "Harlan", "McDaniels",
    "Flynn", "Nguyen", "Peters", "Crayton", "Mallard",
    "Vanston", "Burton", "Blasko", "Janson", "Bonner",
    "Graves", "Miller", "Smith", "Johnson", "Williams",
    "Jones", "Brown", "Garcia", "Rodriguez", "Martinez",
    "Davis", "Hernandez", "Lopez", "Gonzales", "Wilson",
    "Anderson", "Thomas", "Taylor", "Moore", "Jackson",
    "Martin", "Lee", "Perez", "Thompson", "White"
};
const int Passenger::N_LASTNAME = sizeof(Passenger::lastNames) / sizeof(char*);


QString Passenger::createName()
{
    int firstIdx = rand() % N_FIRSTNAME;
    int lastIdx = rand() % N_LASTNAME;

    return QString("%1 %2").arg(firstNames[firstIdx]).arg(lastNames[lastIdx]);
}

TicketSystem::TicketSystem(QObject *parent) : QObject(parent)
{

}

void TicketSystem::clearSales()
{
    soldTickets.clear();
    emit ticketsChanged();
}

void TicketSystem::sellTickets( Route *route, Station *station, QDateTime time, int count )
{
    if( count <= 0 ) return;

    for( int i = count; i > 0; i-- )
    {
        QString name = Passenger::createName();
        soldTickets.push_back(Passenger(name, time, route, station));
    }

    emit ticketsChanged();
}
