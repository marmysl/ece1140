INCLUDEPATH += ../..

QT += testlib
QT += gui
QT += core
QT += core gui serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_testcabincontrols.cpp \
    ../mocs/Train.cpp \
    ../mocs/TrainControllerMoc.cpp \
    ../mocs/SpeedRegulator.cpp \
    ../mocs/BeaconDecoder.cpp

