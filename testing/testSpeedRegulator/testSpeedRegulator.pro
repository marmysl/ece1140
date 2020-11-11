INCLUDEPATH += ../..

QT += testlib core
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_testspeedregulator.cpp \
    ../mocs/Train.cpp \
    ../mocs/TrainControllerMoc.cpp \
    ../mocs/SpeedRegulator.cpp \
    ../mocs/BeaconDecoder.cpp
