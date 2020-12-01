#ifndef TRAINCONTROLLERMOC_H
#define TRAINCONTROLLERMOC_H

#include <string>
#include "TrainMoc.h"
#include "SpeedRegulatorMoc.h"
#include "BeaconDecoderMoc.h"
#include "CTCModeMoc.h"
#include <QDateTime>

class TrainControllerMoc
{
    private:
        TrainMoc *trainModel;
        BeaconDecoderMoc *beacon;
        SpeedRegulatorMoc *speedRegulator;
        CTCModeMoc *mode;
        bool stopTimerStarted;
        bool stopAlreadyOccurred;
        QDateTime start;
        QDateTime now;
    public:
        TrainControllerMoc(CTCModeMoc* modeInit, int numCars, std::string lineType);
        void receiveData(string simData);
        std::string writeData();
	void updateBeaconData(std::string headlights);
        BeaconDecoderMoc* getBeacon();
        SpeedRegulatorMoc* getSpeedRegulator();
        TrainMoc* getTrainModel();
};

#endif // TRAINCONTROLLERMOC_H
