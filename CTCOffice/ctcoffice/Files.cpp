#include "Files.h"
#include "ui_files.h"

#include <fstream>
#include <iostream>

Files::Files(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Files)
{
    ui->setupUi(this);
}

Files::~Files()
{
    delete ui;
}

void Files::mapDisplay(){
    QPixmap mapfile("/Users/christopherkeach/Documents/Junior Semester 1/1140/Github/map.png");
    ui->lblMap->setPixmap(mapfile);
    ui->lblMap->setScaledContents(true);
}

void Files::scheduleParser(){
    //std::ifstream sched;
    //sched.open("excel_sheet");
}
