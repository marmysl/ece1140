#include "trackmodeldisplay.h"
#include "ui_trackmodeldisplay.h"
#include "trackmodel_main.hpp"
#include "routingtestdialog.h"
#include "weatherstation.h"
#include "timetracker.h"
#include "ticketsystem.h"
#include "ticketsdialog.h"

#include <QDebug>

TrackModelDisplay::TrackModelDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrackModelDisplay)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~(Qt::WindowStaysOnTopHint));

    ui->statusBar->addPermanentWidget(&sysTimeLabel, 1);

    sigIndicatorDelegate = new SignalIndicator(this);

    ui->blocktableView->setModel(&blockTable);
    ui->blocktableView->resizeColumnsToContents();
    ui->blocktableView->setItemDelegateForColumn(BlockTableModel::COL_RSIG, sigIndicatorDelegate);
    ui->blocktableView->setItemDelegateForColumn(BlockTableModel::COL_FSIG, sigIndicatorDelegate);

    ui->switchTableView->setModel(&switchTable);
    ui->switchTableView->resizeColumnsToContents();

    ui->signalDirCombo->addItems({"FWD", "REV"});
    ui->signalCombo->addItems({"Red", "Yellow", "Green"});

    connect(systemClock, &TimeTracker::timeAdvanced, this, &TrackModelDisplay::on_timeAdvanced);
}

TrackModelDisplay::~TrackModelDisplay()
{
    delete ui;
    delete sigIndicatorDelegate;
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
    if( !newStation )
    {
        qDebug() << "[TrackModel] Station " << arg1 << " not found";
        selectedStation = nullptr;
        ui->applyStationPropsButton->setEnabled(false);
        ui->clearPlatformButton->setEnabled(false);
    }
    else
    {
        selectedStation = newStation;
        updateStationDisplay();
        ui->applyStationPropsButton->setEnabled(true);
        ui->clearPlatformButton->setEnabled(true);
    }
}

void TrackModelDisplay::on_applyStationPropsButton_clicked()
{
    if( !selectedRoute || !selectedStation ) return;

    int nToAdd = ui->passCountInput->value();

    ticketSystem->sellTickets(selectedRoute->layoutRoute, selectedStation->layoutStation, systemClock->currentTime(), nToAdd);
    selectedStation->numPassengers += nToAdd;

    updateStationDisplay();

    qDebug() << "[TrackModel]" << nToAdd << "passengers added to station" << selectedStation->name();
}

void TrackModelDisplay::on_clearPlatformButton_clicked()
{
    if( !selectedStation ) return;

    selectedStation->numPassengers = 0;
    updateStationDisplay();

    qDebug() << "[TrackModel] Passengers cleared from station" << selectedStation->name();
}

void TrackModelDisplay::on_blocktableView_clicked(const QModelIndex &index)
{
    // when a row in the block table is selected
    int row = index.row();

    using namespace TrackModel;

    selectedBlock = blockTable.getBlockAtIdx(row);
    if( selectedBlock != NULL )
    {
        ui->blockNumLabel->setText(QString("Editing Block %1").arg(selectedBlock->id()));

        BlockFault &curFaults = selectedBlock->faults;
        ui->pwrFailCheck->setChecked(isFaultSet(curFaults, FAULT_POWER_FAIL));
        ui->circFailCheck->setChecked(isFaultSet(curFaults, FAULT_CIRCUIT_FAIL));
        ui->brknRailCheck->setChecked(isFaultSet(curFaults, FAULT_BROKEN_RAIL));

        ui->applyFaultsButton->setEnabled(true);
        ui->applySignalButton->setEnabled(true);
    }
    else
    {
        // selectedBlock == NULL
        ui->blockNumLabel->setText("No Block Selected");

        ui->pwrFailCheck->setChecked(false);
        ui->circFailCheck->setChecked(false);
        ui->brknRailCheck->setChecked(false);

        ui->applyFaultsButton->setEnabled(false);
        ui->applySignalButton->setEnabled(false);
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


void TrackModelDisplay::on_reloadLayoutButton_clicked()
{
    TrackModel::initializeTrackModel();
}

void TrackModelDisplay::on_testRouteButton_clicked()
{
    RoutingTestDialog rtd(selectedRoute->layoutRoute, this);
    rtd.exec();
}

void TrackModelDisplay::on_timeAdvanced( const QDateTime &newTime, qint64 delta )
{
    sysTimeLabel.setText("System Time:  " + newTime.toString());
    ui->envTempLabel->setText(QString::fromStdString(weather->getTempFString()));

    if( weather->isBelowFreezing() )
    {
        ui->heatersStatLabel->setText("On");
        ui->heatersOnFlag->setValue(true);
    }
    else
    {
        ui->heatersStatLabel->setText("Off");
        ui->heatersOnFlag->setValue(false);
    }
}

void TrackModelDisplay::on_applySignalButton_clicked()
{
    int selected = ui->signalCombo->currentIndex();

    if( ui->signalDirCombo->currentIndex() )
    {
        selectedBlock->rSignal = static_cast<TrackModel::SignalState>(selected);
    }
    else selectedBlock->fSignal = static_cast<TrackModel::SignalState>(selected);

    blockTable.on_blockStatusUpdated(selectedBlock->id());
}

void TrackModelDisplay::on_displayTicketsButton_clicked()
{
    TicketsDialog diag(this);
    diag.exec();
}
