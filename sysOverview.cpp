#include "sysOverview.h"
#include "ui_sysOverview.h"

SystemWindow::SystemWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SystemWindow)
{
    ui->setupUi(this);
}

SystemWindow::~SystemWindow()
{
    delete ui;
}

