#include "CTCOffice/ctcoffice/ctc_main.h"
#include "HWTrackController/HWTrackController_main.h"
#include "SWTrackController/TrackController.h"
#include "TrackModel/tracklayout.hpp"
#include "TrackModel/trackmodel_test.hpp"
#include "HWTrainController/HWTrainController_main.h"
#include "SWTrainController/SWTrainController.h"

#include <QApplication>

TrackModel::Route *blueLineLayout;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    blueLineLayout = initTestLayout();

    init_CTC(argc, argv);
    init_HWTrackController();
    init_SWTrackController();
    //init_HWTrainController();
    init_SWTrainController(argc, argv);

    return a.exec();
}
