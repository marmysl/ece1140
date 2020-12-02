#pragma once

#include "hw_sw_interfaces.h"
#include "CTCOffice/ctcoffice/CTCMode.h"
#include <unordered_map>
#include <QApplication>

extern QApplication *mk1_app;

extern std::unordered_map<int, ITrainController *> activeTrains;
extern int nextTrainId;

/*! Instantiate a new HW or SW Train */
void createNewTrain(CTCMode*, int, std::string);

/*! Remove the train with the given id from the active train list */
void forgetTrain( int id );
