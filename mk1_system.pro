QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CTCOffice/ctcoffice/CTCDispatch.cpp \
    CTCOffice/ctcoffice/CTCSignals.cpp \
    CTCOffice/ctcoffice/main.cpp \
    CTCOffice/ctcoffice/mainwindow.cpp \
    CTCOffice/ctcoffice/tracklayout.cpp \
    HWTrackController/CTCSignals.cpp \
    HWTrackController/FailureDetector.cpp \
    HWTrackController/ManualOverride.cpp \
    HWTrackController/Region.cpp \
    HWTrackController/SerialPort.cpp \
    HWTrackController/Track.cpp \
    HWTrackController/main_checker.cpp \
    HWTrainController/CabinControls.cpp \
    HWTrainController/SerialPort.cpp \
    HWTrainController/SpeedRegulator.cpp \
    HWTrainController/TrainController.cpp \
    HWTrainController/main.cpp \
    HWTrainController/test.cpp \
    SWTrackController/BlockCntrl.cpp \
    SWTrackController/TrackController.cpp \
    SWTrackController/trackcntrl_main.cpp \
    SWTrainController/TrainCGUI.cpp \
    SWTrainController/TrainController.cpp \
    SWTrainController/TrainController_main.cpp \
    TrackModel/tracklayout.cpp \
    TrackModel/trackmodel.cpp \
    TrackModel/trackmodeltest.cpp \
    TrainModel/Train.cpp \
    TrainModel/TrainModelMath.cpp \
    TrainModel/TrainModelUI.cpp \
    TrainModel/TrainModelUpdateBlock.cpp \
    TrainModel/main.cpp \
    main.cpp \
    sysOverview.cpp

HEADERS += \
    CTCOffice/ctcoffice/CTCDispatch.h \
    CTCOffice/ctcoffice/CTCSignals.h \
    CTCOffice/ctcoffice/mainwindow.h \
    HWTrackController/CTCSignals.hpp \
    HWTrackController/FailureDetector.hpp \
    HWTrackController/ManualOverride.hpp \
    HWTrackController/Region.hpp \
    HWTrackController/SerialPort.hpp \
    HWTrackController/Track.hpp \
    HWTrainController/CabinControls.h \
    HWTrainController/SerialPort.hpp \
    HWTrainController/SpeedRegulator.h \
    HWTrainController/TrainController.h \
    SWTrackController/BlockCntrl.h \
    SWTrackController/CTCSignals.h \
    SWTrackController/TrackController.h \
    SWTrainController/TrainCGUI.h \
    SWTrainController/TrainController.h \
    SWTrainController/ui_TrainController.h \
    TrackModel/tracklayout.hpp \
    TrackModel/trackmodel_controller.hpp \
    TrackModel/trackmodel_test.hpp \
    TrackModel/trackmodel_train.hpp \
    TrackModel/trackmodel_types.hpp \
    TrainModel/Train.h \
    TrainModel/TrainModelMath.h \
    TrainModel/TrainModelUI.h \
    TrainModel/TrainModelUpdateBlock.h \
    sysOverview.h

FORMS += \
    CTCOffice/ctcoffice/mainwindow.ui \
    SWTrainController/TrainController.ui \
    TrainModel/TrainModelUI.ui \
    sysOverview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CTCOffice/.qmake.stash \
    CTCOffice/ctcoffice/ctcoffice_en_US.ts \
    SWTrainController/.qmake.stash \
    TrackModel/.gitignore \
    TrackModel/.vscode/c_cpp_properties.json \
    TrackModel/.vscode/launch.json \
    TrackModel/.vscode/settings.json \
    TrackModel/.vscode/tasks.json \
    TrackModel/blue_line.csv \
    TrackModel/trackmodel.exe \
    TrainModel/.DS_Store

SUBDIRS += \
    CTCOffice/ctcoffice/ctcoffice.pro \
    SWTrainController/traincontroller.pro \
    TrainModel/TrainModel.pro
