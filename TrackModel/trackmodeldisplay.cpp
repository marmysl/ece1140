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
    ui->blocktableView->resizeColumnsToContents();

    ui->switchTableView->setModel(&switchTable);
    ui->switchTableView->resizeColumnsToContents();
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
    switchTable.resetRoute(newRoute->layoutRoute);

    ui->stationSelector->clear();
    for( auto &s : newRoute->layoutRoute->stations )
    {
        ui->stationSelector->addItem(QString::fromStdString(s->name));
    }
}

void TrackModelDisplay::notifyBlockUpdated( TrackModel::RouteStatus *route, int blockId )
{
    if( route != selectedRoute ) return;
    blockTable.on_blockStatusUpdated(blockId);
}

void TrackModelDisplay::notifySwitchUpdated( TrackModel::Route *route, int switchId )
{
    if( route != selectedRoute->layoutRoute ) return;
    switchTable.on_switchStatusUpdated(switchId);
}

void TrackModelDisplay::updateStationDisplay()
{
    ui->passCountLabel->setText(QString(selectedStation->numPassengers));
    ui->passCountInput->setValue(selectedStation->numPassengers);
}

void TrackModelDisplay::notifyStationUpdated(TrackModel::Route *route, std::string stationName)
{
    if( route != selectedRoute->layoutRoute ) return;
    if( selectedStation == NULL || stationName.compare(selectedStation->layoutStation->name) ) return;
    updateStationDisplay();
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

void TrackModelDisplay::on_stationSelector_currentTextChanged(const QString &arg1)
{
    TrackModel::StationStatus *newStation = selectedRoute->getStationStatus(arg1.toStdString());
    if( newStation == NULL )
    {
        qDebug() << "[TrackModel] Station " << arg1 << " not found";
    }
    else
    {
        selectedStation = newStation;
        updateStationDisplay();
    }
}
