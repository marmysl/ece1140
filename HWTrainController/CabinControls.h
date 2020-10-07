#ifndef CABINCONTROLS_H
#define CABINCONTROLS_H

#include "SerialPort.hpp"

class CabinControls
{
	private:
		bool cabinLights;
		bool cabinAc;
		bool cabinHeat;
		bool cabinDoors;
		bool cabinAdvertisements;
		bool cabinAnnouncements;

	public:
		CabinControls();
		void cabinLightsOn();
		void cabinLightsOff();
		void cabinAcOn();
		void cabinAcOff();
		void cabinHeatOn();
		void cabinHeatOff();
		void cabinDoorsOpen();
		void cabinDoorsClosed();
		void cabinAnnouncementsOn();
		void cabinAnnouncementsOff();
		void cabinAdvertisementsOn();
		void cabinAdvertisementsOff();
		bool getCabinLights();
		bool getCabinAc();
		bool getCabinHeat();
		bool getCabinDoors();
		bool getCabinAnnouncements();
		bool getCabinAdvertisements();
};

#endif