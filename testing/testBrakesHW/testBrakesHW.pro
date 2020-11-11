INCLUDEPATH += ../..

QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    ../../TrainModel/Train.h
    ../../HWTrainController/TrainController.h
    ../../HWTrainController/SpeedRegulator.h

SOURCES += \
    tst_testbrakes.cpp \
    ../../TrainModel/Train.cpp
    ../../HWTrainController/TrainController.cpp
    ../../HWTrainController/SpeedRegulator.cpp

