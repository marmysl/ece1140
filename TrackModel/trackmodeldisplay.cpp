#include "trackmodeldisplay.h"
#include "ui_trackmodeldisplay.h"

TrackModelDisplay::TrackModelDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackModelDisplay)
{
    ui->setupUi(this);
}

TrackModelDisplay::~TrackModelDisplay()
{
    delete ui;
}

void TrackModelDisplay::on_regionComboBox_currentIndexChanged(int index)
{

}
