#include "serialportdialog.h"

#include "CTCOffice/ctcoffice/ctc_main.h"
#include "HWTrackController/HWTrackController_main.h"
#include "SWTrackController/TrackController.h"
#include "TrackModel/tracklayout.hpp"
#include "TrackModel/trackmodel_main.hpp"
#include "HWTrainController/HWTrainController_main.h"
#include "SWTrainController/SWTrainController_main.h"

#include <iostream>
#include <QApplication>
#include <QDebug>

TrackModel::RouteFile blueLine {"Blue Line", "blue_line.csv"};

SerialPortDialog *hwPortsDialog;

int mainArgc;
char **mainArgv;

void createNewTrain() {
    SWTrainController();
}

int main(int argc, char *argv[])
{
    mainArgc = argc;
    mainArgv = argv;

    QApplication a(argc, argv);

    TrackModel::routesToLoad.push_back(blueLine);
    int initResult = TrackModel::initializeTrackModel();
    if( initResult < 0 )
    {
        qDebug() << "Failed to load track model";
        a.quit();
        return EXIT_FAILURE;
    }

    // display modal dialog to select HW component serial ports
    hwPortsDialog = new SerialPortDialog();
    int portsResult = hwPortsDialog->exec();

    // if the dialog was X'd out then quit, because we can't confirm the HW config
    if( portsResult != QDialog::Accepted )
    {
        a.quit();
        return EXIT_SUCCESS;
    }

    init_CTC(argc, argv);
    //init_HWTrackController();
    //init_SWTrackController();
    //init_HWTrainController();

    return a.exec();
}
