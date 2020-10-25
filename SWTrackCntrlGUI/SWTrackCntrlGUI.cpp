#include "SWTrackCntrlGUI.h"
#include "ui_SWTrackCntrlGUI.h"

SWTrackCntrlGUI::SWTrackCntrlGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SWTrackCntrlGUI)
{
    ui->setupUi(this);
}

SWTrackCntrlGUI::~SWTrackCntrlGUI()
{
    delete ui;
}

