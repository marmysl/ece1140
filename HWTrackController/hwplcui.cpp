#include "hwplcui.h"
#include "ui_hwplcui.h"

HWPLCUI::HWPLCUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HWPLCUI)
{
    ui->setupUi(this);
}

HWPLCUI::~HWPLCUI()
{
    delete ui;
}

// Select File
void HWPLCUI::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose PLC"), QFileInfo().absolutePath(), tr("PLC Files (*.txt)"));
    ui->fileName->setText(filename);

    //TrackModel::routesToLoad[selectedIndex].layoutFile = fileName;
    //fileTable.signalChange(selectedIndex);
}

void HWPLCUI::on_comboBox_currentIndexChanged(int index)
{
    // index corresponds to a line, or do QString
}
