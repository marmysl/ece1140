
TEMPLATE = subdirs

SOURCES += \
    mocs/TrainMoc.cpp \
    mocs/TrainControllerMoc.cpp \
    mocs/SpeedRegulatorMoc.cpp \
    mocs/BeaconDecoderMoc.cpp \
    mocs/CTCModeMoc.cpp

SUBDIRS += \
	testBeaconDecoder \
	testCabinControls \
	testLayout \
	testRouting \
	testSpeedRegulator

CONFIG += ordered
