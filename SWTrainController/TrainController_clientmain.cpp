/* This  is the "main" file for the Train Controller SW module.*/

#include "TrainCGUI.h"
#include "TrainController.h"

#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

