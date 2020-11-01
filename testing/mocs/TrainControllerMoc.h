#ifndef TRAINCONTROLLERMOC_H
#define TRAINCONTROLLERMOC_H

#include <string>
#include "TrainMoc.h"
#include "SpeedRegulatorMoc.h"
#include "BeaconDecoderMoc.h"

class TrainControllerMoc
{
    private:
        TrainMoc *trainModel;
        BeaconDecoderMoc *beacon;
        SpeedRegulatorMoc *speedRegulator;
    public:
        TrainControllerMoc();
        void receiveData(string simData);
        std::string writeData();
        BeaconDecoderMoc* getBeacon();
        SpeedRegulatorMoc* getSpeedRegulator();
        TrainMoc* getTrainModel();
};

#endif // TRAINCONTROLLERMOC_H
