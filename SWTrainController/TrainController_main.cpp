/* This  is the "main" file for the Train Controller SW module.*/

#include "TrainCGUI.h"
#include "SWTrainController.h"

#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{

    SWTrainController* tc1 = new SWTrainController(argc, argv);

    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    */

    std::cout << "I am complete\n";
    return 0;
}

