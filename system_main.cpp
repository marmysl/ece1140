#include "timetracker.h"
#include "weatherstation.h"
#include "serialportdialog.h"

#include "system_main.h"

#include "CTCOffice/ctcoffice/ctc_main.h"
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

std::unordered_map<int, ITrainController *> activeTrains;
int nextTrainId = 1;

void createNewTrain() {
    ITrainController *newTrain;

    if( nextTrainId == 1 )
    {
        newTrain = new TrainController();
    }
    else
    {
        newTrain = new SWTrainController();
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
    QDateTime startTime = QDate(2020, 11, 20).startOfDay();
    systemClock = new TimeTracker(startTime, 500, 1800, mk1_app);
    QObject::connect(systemClock, &TimeTracker::timeAdvanced, &weather, &WeatherStation::onTimeUpdate);

    TrackModel::routesToLoad.push_back(blueLine);
    int initResult = TrackModel::initializeTrackModel();
    if( initResult < 0 )
    {
        qDebug() << "Failed to load track model";
        mk1_app->quit();
        return EXIT_FAILURE;
    }

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
    //init_SWTrackController();
    //init_HWTrainController();

    systemClock->play();

    mk1_app->exec();

    return EXIT_SUCCESS;
}
