QT       += core gui
QT += location

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TrainCGUI.cpp \
    TrainController.cpp \
    TrainController_main.cpp


HEADERS += \
    TrainCGUI.h \
    TrainController.h

FORMS += \
    TrainController.ui

macx {

    QMAKE_CFLAGS += -std=c++11 -stdlib=libc++

    QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++

    # LIBS += -L"/usr/local/Cellar/boost/1.73.0/lib" -lboost_random

    # INCLUDEPATH += "/usr/local/Cellar/boost/1.73.0/include"

}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
