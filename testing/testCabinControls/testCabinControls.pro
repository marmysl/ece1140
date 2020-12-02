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
    ../mocs/TrainMoc.cpp \
    ../mocs/TrainControllerMoc.cpp \
    ../mocs/SpeedRegulatorMoc.cpp \
    ../mocs/BeaconDecoderMoc.cpp \
    ../mocs/CTCModeMoc.cpp

HEADERS += \
    ../mocs/TrainMoc.h \
    ../mocs/TrainControllerMoc.h \
    ../mocs/SpeedRegulatorMoc.h \
    ../mocs/BeaconDecoderMoc.h \
    ../mocs/CTCModeMoc.h
