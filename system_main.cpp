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
#include "TrackModel/layoutdialog.h"
#include "HWTrainController/TrainController.h"
#include "SWTrainController/SWTrainController_main.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>

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

    // load config or create default
    if( !mk1Config.tryLoadConfig() )
    {
        // couldn't load, create new
        mk1Config.applyDefaultConfig();
        mk1Config.saveConfig();
        qDebug() << "[System] Created new config file @ " << QString::fromStdString(mk1Config.configPath);
    }

    // initialize system timer
    systemClock = new TimeTracker(QDateTime::currentDateTime(), 100, 1, mk1_app);
    weather = new WeatherStation(mk1_app);
    QObject::connect(systemClock, &TimeTracker::timeAdvanced, weather, &WeatherStation::onTimeUpdate);

    systemDialog = new SystemSettingsDialog();
    systemDialog->show();

    // Track model stuff
    // Get the files we should load from the config
    int nLines = mk1Config.getIntVal("nlines");
    for( int i = 0; i < nLines; i++ )
    {
        std::string nameKey = QString("line_n%0").arg(i).toStdString();
        std::string fileKey = QString("line_f%0").arg(i).toStdString();

        QString name = QString::fromStdString(mk1Config.getStringVal(nameKey));
        QString file = QString::fromStdString(mk1Config.getStringVal(fileKey));

        RouteFile newEntry(name, file);
        routesToLoad.push_back(newEntry);
    }

    if( !mk1Config.loadedFromFile )
    {
        TrackModel::changeLayouts();
    }

    // setup the track model internals and UI
    int initResult = TrackModel::initializeTrackModel();
    if( initResult < 0 )
    {
        qDebug() << "Failed to load track model";
        mk1_app->quit();
        return EXIT_FAILURE;
    }

    // create the ticketing and passenger gen system
    ticketSystem = new TicketSystem(mk1_app);
    QObject::connect(systemClock, &TimeTracker::timeAdvanced, ticketSystem, &TicketSystem::onTimeUpdate);

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

    // save the config to disk
    mk1Config.saveConfig();

    return EXIT_SUCCESS;
}


// System Config File handling
SystemConfig mk1Config;

bool SystemConfig::tryLoadConfig()
{
    entries.clear();

    std::ifstream configFile;

    QFileInfo fInfo(CONFIG_PATH);
    configPath = fInfo.absoluteFilePath().toStdString();
    configFile.open(configPath, std::ios::in);

    if( !configFile.is_open() )
    {
        qDebug() << "[System] Unable to open config file";
        return false;
    }

    std::string nextLine;
    std::stringstream buf = std::stringstream ();

    int fileLine = 1;

    // for each line of the config file
    while( getline(configFile, nextLine) )
    {
        // check if line is commented
        if( (nextLine.length() == 0) || (nextLine.at(0) == ';') )
        {
            fileLine += 1;
            continue;
        }

        // split line into key and value
        size_t eqIndex = nextLine.find('=');
        if( (eqIndex != std::string::npos) && (eqIndex < nextLine.length() - 1) )
        {
            std::string key = nextLine.substr(0, eqIndex);
            std::string value = nextLine.substr(eqIndex + 1);

            entries[key] = value;
        }
        else
        {
            // bad line
            qDebug() << "[System] Bad key/value on line " << fileLine << " in config";
            loadedFromFile = false;
            throw std::invalid_argument("Couldn't load config file");
        }

        fileLine += 1;
    }

    qDebug() << "[System] Successfully loaded config";
    loadedFromFile = true;
    return true;
}

void SystemConfig::saveConfig()
{
    std::ofstream configFile;

    QFileInfo fInfo(CONFIG_PATH);
    configPath = fInfo.absoluteFilePath().toStdString();
    configFile.open(configPath, std::ios::out | std::ios::trunc);

    if( !configFile.is_open() )
    {
        qDebug() << "[System] Unable to save config file";
        return;
    }

    for( auto &kvp : entries )
    {
        configFile << kvp.first << "=" << kvp.second << std::endl;
    }

    configFile.close();
    qDebug() << "[System] Config saved";
}

void SystemConfig::applyDefaultConfig()
{
    entries.clear();
    for( int i = 0; i < N_DEF_CONF_ENTRIES; i++ )
    {
        auto &kvp = defaultConfig[i];
        entries[kvp.first] = kvp.second;
    }

    loadedFromFile = false;
}

const QString SystemConfig::CONFIG_PATH = "mk1_config.ini";

const int N_DEF_CONF_ENTRIES = 5;
std::pair<std::string, std::string> defaultConfig[N_DEF_CONF_ENTRIES]
{
    {"nlines", "2"},
    {"line_n0", "Green Line"},
    {"line_f0", "green_line.csv"},
    {"line_n1", "Red Line"},
    {"line_f1", "red_line.csv"}
};
