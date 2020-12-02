#include "trackmodeldisplay.h"
#include "ui_trackmodeldisplay.h"
#include "trackmodel_main.hpp"
#include "routingtestdialog.h"
#include "weatherstation.h"
#include "timetracker.h"
#include "ticketsystem.h"
#include "ticketsdialog.h"
#include "ui_blockgeodialog.h"

#include <QDebug>

TrackModelDisplay::TrackModelDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrackModelDisplay)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~(Qt::WindowStaysOnTopHint));

    ui->statusBar->addPermanentWidget(&sysTimeLabel, 1);

    layoutBlockDiag = new BlockGeoDialog(this);

    ui->signalDirCombo->addItems({"FWD", "REV"});
    ui->signalCombo->addItems({"Red", "Yellow", "Green"});

    connect(systemClock, &TimeTracker::timeAdvanced, this, &TrackModelDisplay::on_timeAdvanced);
}

TrackModelDisplay::~TrackModelDisplay()
{
    delete ui;
    delete layoutBlockDiag;
}

void TrackModelDisplay::setRegionList( std::vector<TrackModel::Route *> *routeList ) {
    ui->regionComboBox->clear();

    for( TrackModel::Route *&rt : *routeList ) {
        ui->regionComboBox->addItem(QString(rt->name.c_str()));
    }
}

void TrackModelDisplay::setRoute( TrackModel::RouteStatus *newRoute ) {
    selectedRoute = newRoute;
    ui->routeMap->setRoute(newRoute);

    // blocks
    blockSelectList.clear();
    for( auto &kvp : newRoute->blockMap ) blockSelectList.push_back(kvp.first);
    std::sort(blockSelectList.begin(), blockSelectList.end());

    for( int &n : blockSelectList )
    {
        if( n )
        {
            ui->blockSelector->addItem(QString::number(n));
        }
        else
        {
            ui->blockSelector->addItem(QString("0 (Yard)"));
        }
    }

    // stations
    ui->stationSelector->clear();
    QStringList stationList;

    for( auto &s : newRoute->layoutRoute->stations )
    {
        stationList.push_back(QString::fromStdString(s->name));
    }

    std::sort(stationList.begin(), stationList.end());
    ui->stationSelector->addItems(stationList);

    // switches
    ui->switchSelector->clear();
    QStringList switchSelectList;

    for( auto &sw : newRoute->layoutRoute->switches )
    {
        switchSelectList.push_back(QString::number(sw.first));
    }

    std::sort(switchSelectList.begin(), switchSelectList.end());
    ui->switchSelector->addItems(switchSelectList);
}

void TrackModelDisplay::notifySwitchUpdated( TrackModel::Route *route, int switchId )
{
    if( route != selectedRoute->layoutRoute ) return;
    ui->routeMap->update();
    updateSwitchDisplay();
}

void TrackModelDisplay::notifyStationUpdated(TrackModel::Route *route, std::string stationName)
{
    if( route != selectedRoute->layoutRoute ) return;
    if( !selectedStation || stationName.compare(selectedStation->layoutStation->name) ) return;
    updateStationDisplay();
}

void TrackModelDisplay::on_regionComboBox_currentTextChanged(const QString &arg1)
{
    qDebug() << "[TrackModel] Displayed region changed to " << arg1;

    TrackModel::RouteStatus *newRoute = TrackModel::getRouteStatus(arg1);

    if( !newRoute ) {
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
        selectedStation = nullptr;
        ui->applyStationPropsButton->setEnabled(false);
        return;
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

void TrackModelDisplay::on_blockSelector_currentIndexChanged(int index)
{
    // when a row in the block table is selected
    int blockNum = blockSelectList[index];

    using namespace TrackModel;

    selectedBlock = selectedRoute->getBlockStatus(blockNum);
    updateBlockDisplay();
}

void TrackModelDisplay::on_applyFaultsButton_clicked()
{
    using namespace TrackModel;

    if( !selectedBlock ) return;

    BlockFault newFaults = FAULT_NONE;
    if( ui->pwrFailCheck->isChecked() ) newFaults |= FAULT_POWER_FAIL;
    if( ui->circFailCheck->isChecked() ) newFaults |= FAULT_CIRCUIT_FAIL;
    if( ui->brknRailCheck->isChecked() ) newFaults |= FAULT_BROKEN_RAIL;

    selectedBlock->setFaults(newFaults);

    qDebug() << "[TrackModel] Applied faults " << getFaultString(newFaults) << " to block " << selectedBlock->id();
}


void TrackModelDisplay::on_reloadLayoutButton_clicked()
{
    TrackModel::changeLayouts();
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

    BlockDir side = (ui->signalDirCombo->currentIndex()) ? BLK_FORWARD : BLK_REVERSE;
    selectedBlock->setSignal(side, static_cast<TrackModel::SignalState>(selected));
}

void TrackModelDisplay::on_displayTicketsButton_clicked()
{
    TicketsDialog diag(this);
    diag.exec();
}

void TrackModelDisplay::on_blockUpdated( TrackModel::RouteStatus *sender, int blockId )
{
    if( sender == selectedRoute )
    {
        ui->routeMap->update();
        updateBlockDisplay();
    }
}

void TrackModelDisplay::on_showBlockGeoButton_clicked()
{
    if( !selectedBlock ) return;
    layoutBlockDiag->show();
}

void TrackModelDisplay::on_switchSelector_currentTextChanged(const QString &arg1)
{
    bool ok;
    int switchId = arg1.toInt(&ok);
    if( selectedRoute && ok )
    {
        selectedSwitch = selectedRoute->layoutRoute->getSwitch(switchId);
    }

    updateSwitchDisplay();
}

void TrackModelDisplay::on_applySwitchButton_clicked()
{
    if( !selectedSwitch ) return;

    SwitchState newState = (ui->swDivergeCheckBox->isChecked()) ? SW_DIVERGING : SW_STRAIGHT;
    selectedSwitch->setDirection(newState);
    ui->switchStateLabel->setText((newState == SW_DIVERGING) ? "Diverging" : "Straight");

    notifySwitchUpdated(selectedRoute->layoutRoute, selectedSwitch->fromBlock->id);
}


void TrackModelDisplay::updateStationDisplay()
{
    ui->passCountLabel->setText(QString::number(selectedStation->numPassengers));
}

void TrackModelDisplay::updateSwitchDisplay()
{
    if( selectedSwitch )
    {
        if( selectedSwitch->direction == SW_DIVERGING )
        {
            ui->switchStateLabel->setText("Diverging");
            ui->swDivergeCheckBox->setChecked(true);
        }
        else
        {
            ui->switchStateLabel->setText("Straight");
            ui->swDivergeCheckBox->setChecked(false);
        }

        ui->applySwitchButton->setEnabled(true);
    }
    else
    {
        ui->switchStateLabel->setText("N/A");
        ui->applySwitchButton->setEnabled(false);
    }
}

static QString genBeaconString( const BeaconData& beacon )
{
    if( !beacon.hasData() ) return QString("None");

    std::stringstream sb;
    bool first = true;

    if( beacon.updateLights )
    {
        sb << "Lights ";
        sb << ((beacon.newLightState) ? "On" : "Off");
        first = false;
    }

    if( beacon.stationHere )
    {
        if( !first ) sb << ", ";
        sb << "Station: " << beacon.stationName << " (" << strForSide(beacon.platformSide) << ")";
    }
    else if( beacon.stationUpcoming )
    {
        if( !first ) sb << ", ";

        sb << "Upcoming: " << beacon.stationName << " (" << strForSide(beacon.platformSide) << ")";
    }
    else if( beacon.stationUpcomingFar )
    {
        if( !first ) sb << ", ";
        sb << "Far: " << beacon.stationName << " (" << strForSide(beacon.platformSide) << ")";
    }

    return QString::fromStdString(sb.str());
}

void TrackModelDisplay::updateBlockDisplay()
{
    if( selectedBlock )
    {
        BlockFault curFaults = selectedBlock->getFaults();
        ui->pwrFailCheck->setChecked(isFaultSet(curFaults, FAULT_POWER_FAIL));
        ui->circFailCheck->setChecked(isFaultSet(curFaults, FAULT_CIRCUIT_FAIL));
        ui->brknRailCheck->setChecked(isFaultSet(curFaults, FAULT_BROKEN_RAIL));

        TrackCircuitData data = selectedBlock->getCircuitData();
        ui->speedCmdLabel->setText(QString("Speed Cmd: %0 kph").arg(data.decodeSpeed()));
        ui->authCmdLabel->setText(QString("Auth Cmd: %0").arg(data.decodeAuthority()));

        Block *layBlk = selectedBlock->layoutBlock;
        ui->fwdBeaconLabel->setText(genBeaconString(layBlk->forwardBeacon));
        ui->revBeaconLabel->setText(genBeaconString(layBlk->reverseBeacon));

        layoutBlockDiag->setBlock(selectedBlock->layoutBlock);

        ui->applyFaultsButton->setEnabled(true);
        ui->applySignalButton->setEnabled(true);
        ui->showBlockGeoButton->setEnabled(true);
    }
    else
    {
        // selectedBlock == NULL

        ui->pwrFailCheck->setChecked(false);
        ui->circFailCheck->setChecked(false);
        ui->brknRailCheck->setChecked(false);

        ui->speedCmdLabel->setText("Speed Cmd:");
        ui->authCmdLabel->setText("Auth Cmd:");

        ui->fwdBeaconLabel->setText("N/A");
        ui->revBeaconLabel->setText("N/A");

        ui->applyFaultsButton->setEnabled(false);
        ui->applySignalButton->setEnabled(false);
        ui->showBlockGeoButton->setEnabled(false);
    }
}

// End TrackModelDisplay
//============================================================================================



// BlockGeoDialog
//============================================================================================
BlockGeoDialog::BlockGeoDialog(QWidget *parent) : QDialog(parent), ui(new Ui::BlockGeoDialog)
{
    ui->setupUi(this);
}

BlockGeoDialog::~BlockGeoDialog()
{
    delete ui;
}

const QString NODIR_STR("None");
const QString REV_STR("Reverse");
const QString FWD_STR("Forward");
static inline const QString& onewayStr( BlockDir dir )
{
    if( dir == BLK_NODIR ) return NODIR_STR;
    else return (dir == BLK_FORWARD) ? FWD_STR : REV_STR;
}

const QString NA_STR("N/A");
const QString UNDERGROUND("Underground");
const QString ABOVEGROUND("Aboveground");

void BlockGeoDialog::setBlock( TrackModel::Block *block )
{
    displayBlock = block;

    setWindowTitle(QString("Block %0").arg(block->id));
    ui->blockIdLabel->setText(QString::number(block->id));
    ui->sectionLabel->setText(QString::fromStdString(block->section));
    ui->lengthLabel->setText(QString("%0 m").arg(block->length));
    ui->gradeLabel->setText(QString("%0%").arg(block->grade * 100));
    ui->speedLimitLabel->setText(QString("%0 kph").arg(block->speedLimit));
    ui->onewayLabel->setText(onewayStr(block->oneWay));

    PlatformData& platform = block->platform;
    if( platform.exists() )
    {
        QString stationStr = QString("%0 (%1)").arg(QString::fromStdString(platform.station->name)).arg(charForSide(platform.side));
        ui->stationLabel->setText(stationStr);
    }
    else
    {
        ui->stationLabel->setText(NA_STR);
    }

    ui->tunnelLabel->setText(block->underground ? UNDERGROUND : ABOVEGROUND);
}
