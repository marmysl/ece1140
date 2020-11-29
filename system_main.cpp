#include "timetracker.h"
#include "weatherstation.h"
#include "ticketsystem.h"
#include "serialportdialog.h"
#include "systemsettingsdialog.h"

#include "system_main.h"

#include "CTCOffice/ctcoffice/ctc_main.h"
#include "CTCOffice/ctcoffice/CTCMode.h"
#include "HWTrackController/HWTrackController_main.h"
#include "SWTrackController/TrackController.h"
#include "TrackModel/tracklayout.hpp"
#include "TrackModel/trackmodel_main.hpp"
#include "HWTrainController/TrainController.h"
#include "SWTrainController/SWTrainController_main.h"

#include <iostream>
#include <unordered_map>
#include <QApplication>
#include <QDebug>

TrackModel::RouteFile blueLine {"Blue Line", "blue_line.csv"};

QApplication *mk1_app;
SerialPortDialog *hwPortsDialog;
SystemSettingsDialog *systemDialog;

std::unordered_map<int, ITrainController *> activeTrains;
int nextTrainId = 1;

void createNewTrain(CTCMode *mode, int numCars, std::string lineType) {
    ITrainController *newTrain;

    if( trainControllerPort.isConnected() && (nextTrainId == 1) )
    {
        newTrain = new TrainController(mode, numCars, lineType);
    }
    else
    {
        newTrain = new SWTrainController(mode, numCars, lineType);
    }

    newTrain->id = nextTrainId;
    activeTrains.insert({nextTrainId, newTrain});

    nextTrainId += 1;
}

void forgetTrain( int id )
{
    activeTrains.erase(id);
}


int main(int argc, char *argv[])
{
    mk1_app = new QApplication(argc, argv);

    // initialize system timer
    systemClock = new TimeTracker(QDateTime::currentDateTime(), 100, 1, mk1_app);
    weather = new WeatherStation(mk1_app);
    QObject::connect(systemClock, &TimeTracker::timeAdvanced, weather, &WeatherStation::onTimeUpdate);

    systemDialog = new SystemSettingsDialog();
    systemDialog->show();

    TrackModel::routesToLoad.push_back(blueLine);
    int initResult = TrackModel::initializeTrackModel();
    if( initResult < 0 )
    {
        qDebug() << "Failed to load track model";
        mk1_app->quit();
        return EXIT_FAILURE;
    }

    ticketSystem = new TicketSystem(mk1_app);
    //ticketSystem->sellTickets(routes[0], routes[0]->stations[0], systemClock->currentTime(), 20);

    // display modal dialog to select HW component serial ports
    hwPortsDialog = new SerialPortDialog();
    int portsResult = hwPortsDialog->exec();

    // if the dialog was X'd out then quit, because we can't confirm the HW config
    if( portsResult != QDialog::Accepted )
    {
        mk1_app->quit();
        return EXIT_SUCCESS;
    }

    init_CTC(argc, argv);
    //init_HWTrackController();
    init_SWTrackController();
    //init_HWTrainController();

    systemClock->play();

    mk1_app->exec();

    return EXIT_SUCCESS;
}
