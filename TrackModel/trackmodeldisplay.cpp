#include "trackmodeldisplay.h"
#include "ui_trackmodeldisplay.h"
#include "trackmodel_main.hpp"

#include <QDebug>

TrackModelDisplay::TrackModelDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackModelDisplay)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & !(Qt::WindowStaysOnTopHint));

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
    ui->passCountLabel->setText(QString::number(selectedStation->numPassengers));
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
    if( arg1.isEmpty() )
    {
        selectedStation = NULL;
        ui->applyStationPropsButton->setEnabled(false);
    }

    TrackModel::StationStatus *newStation = selectedRoute->getStationStatus(arg1.toStdString());
    if( newStation == NULL )
    {
        qDebug() << "[TrackModel] Station " << arg1 << " not found";
        selectedStation = NULL;
        ui->applyStationPropsButton->setEnabled(false);
    }
    else
    {
        selectedStation = newStation;
        updateStationDisplay();
        ui->applyStationPropsButton->setEnabled(true);
    }
}

void TrackModelDisplay::on_applyStationPropsButton_clicked()
{
    if( selectedStation == NULL ) return;

    int newCount = ui->passCountInput->value();
    selectedStation->numPassengers = newCount;

    updateStationDisplay();

    qDebug() << "[TrackModel] Passenger count set to " << newCount << " at station " << selectedStation->name();
}

void TrackModelDisplay::on_blocktableView_clicked(const QModelIndex &index)
{
    // when a row in the block table is selected
    int row = index.row();

    using namespace TrackModel;

    selectedBlock = blockTable.getBlockAtIdx(row);
    if( selectedBlock != NULL )
    {
        ui->faultBlockNum->display(selectedBlock->id());

        BlockFault &curFaults = selectedBlock->faults;
        ui->pwrFailCheck->setChecked(isFaultSet(curFaults, FAULT_POWER_FAIL));
        ui->circFailCheck->setChecked(isFaultSet(curFaults, FAULT_CIRCUIT_FAIL));
        ui->brknRailCheck->setChecked(isFaultSet(curFaults, FAULT_BROKEN_RAIL));
        ui->applyFaultsButton->setEnabled(true);
    }
    else
    {
        // selectedBlock == NULL
        ui->faultBlockNum->display(0);

        ui->pwrFailCheck->setChecked(false);
        ui->circFailCheck->setChecked(false);
        ui->brknRailCheck->setChecked(false);
        ui->applyFaultsButton->setEnabled(false);
    }
}

void TrackModelDisplay::on_applyFaultsButton_clicked()
{
    using namespace TrackModel;

    if( selectedBlock == NULL ) return;

    BlockFault newFaults = FAULT_NONE;
    if( ui->pwrFailCheck->isChecked() ) newFaults |= FAULT_POWER_FAIL;
    if( ui->circFailCheck->isChecked() ) newFaults |= FAULT_CIRCUIT_FAIL;
    if( ui->brknRailCheck->isChecked() ) newFaults |= FAULT_BROKEN_RAIL;

    selectedBlock->faults = newFaults;
    blockTable.on_blockStatusUpdated(selectedBlock->id());

    qDebug() << "[TrackModel] Applied faults " << getFaultString(newFaults) << " to block " << selectedBlock->id();
}

