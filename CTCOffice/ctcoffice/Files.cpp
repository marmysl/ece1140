#include "Files.h"
#include "ui_files.h"
#include "mainwindow.h"

#include <fstream>
#include <iostream>

#include <QFileInfo>

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

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Map"), QFileInfo().absolutePath(), tr("Map Files (*.png)"));

    std::ifstream mapFile;

    QFileInfo lfInfo(fileName);
    mapFile.open(lfInfo.absoluteFilePath().toStdString(), std::ios::in);

    if( !mapFile.is_open() ) throw std::invalid_argument ("Unable to open map");

    QPixmap mapfile(fileName);
    ui->lblMap->setPixmap(mapfile);
    ui->lblMap->setScaledContents(true);
}
