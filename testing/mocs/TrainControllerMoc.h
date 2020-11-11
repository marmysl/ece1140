#ifndef TRAINCONTROLLERMOC_H
#define TRAINCONTROLLERMOC_H

#include <string>
#include <QObject>
#include "Train.h"
#include "../../HWTrainController/SpeedRegulator.h"
#include "../../HWTrainController/BeaconDecoder.h"

class TrainControllerMoc : public QObject
{
    private:
        Train *trainModel;
        BeaconDecoder *beacon;
        SpeedRegulator *speedRegulator;
        bool mode;
    public:
        TrainControllerMoc(bool m);
        void receiveData(string simData);
        std::string writeData();
        BeaconDecoder* getBeacon();
        SpeedRegulator* getSpeedRegulator();
        Train* getTrainModel();
        void setMode(bool);
        bool getMode();
};

#endif // TRAINCONTROLLERMOC_H
