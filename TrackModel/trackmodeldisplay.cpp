#include "trackmodeldisplay.h"
#include "ui_trackmodeldisplay.h"
#include "trackmodel_main.hpp"

#include <QDebug>

TrackModelDisplay::TrackModelDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackModelDisplay)
{
    ui->setupUi(this);

    ui->blocktableView->setModel(&blockTable);
}

TrackModelDisplay::~TrackModelDisplay()
{
    delete ui;
}

void TrackModelDisplay::setRegionList( std::vector<TrackModel::Route *> *routeList ) {
    ui->regionComboBox->clear();

    for( TrackModel::Route *&rt : *routeList ) {
        ui->regionComboBox->addItem(QString(rt->name.c_str()));
    }
}

void TrackModelDisplay::setRoute( TrackModel::RouteStatus *newRoute ) {
    selectedRoute = newRoute;
    blockTable.resetRoute(newRoute);
}


void TrackModelDisplay::on_regionComboBox_currentTextChanged(const QString &arg1)
{
    qDebug() << "[TrackModel] Displayed region changed to " << arg1;

    TrackModel::RouteStatus *newRoute = TrackModel::getRouteStatus(arg1);

    if( newRoute == NULL ) {
        qDebug() << "[TrackModel] Region " << arg1 << " not found";
    }
    else {
        setRoute(newRoute);
    }
}
