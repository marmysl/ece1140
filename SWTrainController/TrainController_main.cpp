/* This  is the "main" file for the Train Controller SW module.*/

#include "TrainCGUI.h"
#include "TrainController.h"

#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{

    TrainController* tc1 = new TrainController(argc, argv);

    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    */

    std::cout << "I am complete\n";
    return 0;
}

