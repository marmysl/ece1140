
TEMPLATE = subdirs

SOURCES += \
    mocs/TrainMoc.cpp \
    mocs/TrainControllerMoc.cpp \
    mocs/SpeedRegulatorMoc.cpp \
    mocs/BeaconDecoderMoc.cpp

HEADERS += \
    mocs/TrainMoc.h \
    mocs/TrainControllerMoc.h \
    mocs/SpeedRegulatorMoc.h \
    mocs/BeaconDecoderMoc.h

SUBDIRS += \
	testCabinControls \
	testLayout \
	testRouting \
	testSpeedRegulator



CONFIG += ordered
