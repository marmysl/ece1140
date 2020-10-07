#include "CabinControls.h"
CabinControls::CabinControls()
{
	//Initialize all variables to 0
	cabinLights = 0;
	cabinAc = 0;
	cabinHeat = 0;
	cabinDoors = 0;
	cabinAdvertisements = 0;
	cabinAnnouncements = 0;
}
void CabinControls::cabinLightsOn()
{
	cabinLights = 1;
}
void CabinControls::cabinLightsOff()
{
	cabinLights = 0;
}
void CabinControls::cabinAcOn()
{
	cabinAc = 1;
}
void CabinControls::cabinAcOff()
{
	cabinAc = 0;
}
void CabinControls::cabinHeatOn()
{
	cabinHeat = 1;
}
void CabinControls::cabinHeatOff()
{
	cabinHeat = 0;
}
void CabinControls::cabinDoorsOpen()
{
	cabinDoors = 1;
}
void CabinControls::cabinDoorsClosed()
{
	cabinDoors = 0;
}
void CabinControls::cabinAnnouncementsOn()
{
	cabinAnnouncements = 1;
}
void CabinControls::cabinAnnouncementsOff()
{
	cabinAnnouncements = 0;
}
void CabinControls::cabinAdvertisementsOn()
{
	cabinAdvertisements = 1;
}
void CabinControls::cabinAdvertisementsOff()
{
	cabinAdvertisements = 0;
}
bool CabinControls::getCabinLights()
{
	return cabinLights;
}

bool CabinControls::getCabinAc()
{
	return cabinAc;
}

bool CabinControls::getCabinHeat()
{
	return cabinHeat;
}

bool CabinControls::getCabinDoors()
{
	return cabinDoors;
}

bool CabinControls::getCabinAnnouncements()
{
	return cabinAnnouncements;
}

bool CabinControls::getCabinAdvertisements()
{
	return cabinAdvertisements;
}