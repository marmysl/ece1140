#include "ticketsdialog.h"
#include "ui_ticketsdialog.h"
#include "ticketsystem.h"

TicketsDialog::TicketsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketsDialog)
{
    ui->setupUi(this);

    ui->ticketTable->setRowCount(ticketSystem->soldTickets.size());
    ui->ticketTable->setHorizontalHeaderLabels({"Purchased", "Name", "Route", "Station"});

    int row = 0;
    for( Passenger &p : ticketSystem->soldTickets )
    {
        QTableWidgetItem *item = new QTableWidgetItem(p.purchaseTime.toString());
        ui->ticketTable->setItem(row, 0, item);

        item = new QTableWidgetItem(p.name);
        ui->ticketTable->setItem(row, 1, item);

        item = new QTableWidgetItem(QString::fromStdString(p.route->name));
        ui->ticketTable->setItem(row, 2, item);

        item = new QTableWidgetItem(QString::fromStdString(p.startStation->name));
        ui->ticketTable->setItem(row, 3, item);

        row++;
    }
}

TicketsDialog::~TicketsDialog()
{
    delete ui;
}
