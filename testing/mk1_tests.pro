TEMPLATE = subdirs

QT += core

SOURCES += \
    mocs/Train.cpp \
    mocs/TrainControllerMoc.cpp \
    mocs/SpeedRegulator.cpp \
    mocs/BeaconDecoder.cpp

HEADERS += \
    mocs/Train.h \
    mocs/TrainControllerMoc.h \
    mocs/SpeedRegulator.h \
    mocs/BeaconDecoder.h

SUBDIRS += \
	testCabinControls \
	testLayout \
	testRouting \
	testSpeedRegulator


CONFIG += ordered
