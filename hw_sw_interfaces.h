#pragma once

#include "TrainModel/Train.h"

// add to me as needed pls

class ITrainController
{
public:
    /*! Unique train identifier */
    int id;

    /*! Train Model associated with this controller */
    Train *train;

    /*! Called when the train is sent onto the track */
    // probably should have more params, idk
    virtual void dispatch() = 0;
};

class ITrackController
{
public:
    /*! Unique track region identifier */
    int id;
};
