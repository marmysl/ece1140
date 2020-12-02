#pragma once

#include "hw_sw_interfaces.h"
#include "CTCOffice/ctcoffice/CTCMode.h"
#include "mk1_util.hpp"
#include <unordered_map>
#include <QApplication>

extern QApplication *mk1_app;

extern std::unordered_map<int, ITrainController *> activeTrains;
extern int nextTrainId;

/*! Instantiate a new HW or SW Train */
void createNewTrain(CTCMode*, int, std::string);

/*! Remove the train with the given id from the active train list */
void forgetTrain( int id );

class SystemConfig
{
private:
    static const QString CONFIG_PATH;
    std::unordered_map<std::string, std::string> entries;

public:
    bool loadedFromFile;
    std::string configPath;

    bool tryLoadConfig();
    void saveConfig();
    void applyDefaultConfig();

    int getIntVal(std::string key)
    {
        return MK1Util::parseIntStrict(entries[key]);
    }

    float getFloatVal(std::string key)
    {
        return MK1Util::parseFloatStrict(entries[key]);
    }

    std::string getStringVal(std::string key)
    {
        return entries[key];
    }

    void setIntVal(std::string key, int val)
    {
        entries[key] = to_string(val);
    }

    void setFloatVal(std::string key, float val)
    {
        entries[key] = to_string(val);
    }

    void setStringVal(std::string key, std::string val)
    {
        entries[key] = val;
    }
};

extern SystemConfig mk1Config;

extern const int N_DEF_CONF_ENTRIES;
extern std::pair<std::string, std::string> defaultConfig[];
