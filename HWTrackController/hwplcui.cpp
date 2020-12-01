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

// Select File for Green Line
void HWPLCUI::on_greenButton_clicked()
{
    glfilename = QFileDialog::getOpenFileName(this, tr("Choose PLC"), QFileInfo().absolutePath(), tr("PLC Files (*.txt)"));
    ui->greenFile->setText(glfilename);
}

// Select File for Red Line
void HWPLCUI::on_redButton_clicked()
{
    rlfilename = QFileDialog::getOpenFileName(this, tr("Choose PLC"), QFileInfo().absolutePath(), tr("PLC Files (*.txt)"));
    ui->redFile->setText(rlfilename);
}

// Accepting will load + parse PLC file for respective lines
void HWPLCUI::on_buttonBox_accepted()
{
   // upload file
    if (!glfilename.isEmpty()) { greenreg.loadPLC(glfilename);  }
   else if (!rlfilename.isEmpty()) { redreg.loadPLC(rlfilename); }

   // make a track controller object with first file
   HWTrackController* obj = new HWTrackController();
   close();
}
