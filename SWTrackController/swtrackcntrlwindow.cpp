#include "swtrackcntrlwindow.h"
#include "ui_swtrackcntrlwindow.h"

#include <QtLocation/QGeoRoute>

SWTrackCntrlWindow::SWTrackCntrlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SWTrackCntrlWindow)
{
    ui->setupUi(this);
   // timerID = startTimer(1000);
   // count = 0;

    ui->mainWindow->hide();
    PLCfile_present = false;
    ui->CancelButton->hide();


}

void SWTrackCntrlWindow::timerEvent(QTimerEvent *event)
{
    count++;
    //std::cout << "Timer has updated... " << count << std::endl; //debug

    updateWaysides();
}

SWTrackCntrlWindow::~SWTrackCntrlWindow()
{
    killTimer(timerID);
    delete ui;
}

bool SWTrackCntrlWindow::setPLC() {

    setPLCFile(filename);
    return PLCfile_present;
}

void SWTrackCntrlWindow::setBlock() {

    int id_int;
    QString temp = "";
    QString tab = " / ";
    QString final = "";

    for (auto i = wayside.cntrl_blocks.begin(); i != wayside.cntrl_blocks.end(); i++) {
        id_int = *i;
        temp = QString::number(id_int);
        temp = temp % tab;
        final = final % temp;
    }

    ui->waysideBlocksText->setPlainText(final);

}

void SWTrackCntrlWindow::setSwitch() {
    QString switch_head;
    QString switch_tail;
    QString switch_state;

    if (wayside.switch_head != -1) {

        switch_head = QString::number(wayside.switch_head);

        if (wayside.switch_state == 0) {
            switch_tail = QString::number(wayside.switch_tail0);
            switch_state = "straight";
        }
        else {
            switch_tail = QString::number(wayside.switch_tail1);
            switch_state = "diverging";
        }

    }
    else {
        switch_head = "null";
        switch_tail = "null";
        switch_state = "null";
    }


    ui->switchHeadText->setPlainText(switch_head);
    ui->switchTailText->setPlainText(switch_tail);
    ui->switchStateText->setPlainText(switch_state);

}

void SWTrackCntrlWindow::setCrossing() {
    QString crossing_id;
    QString state;

    if (wayside.crossing_id != -1) {
        crossing_id = QString::number(wayside.crossing_id);
        if (wayside.cross_state == true) {
            state = "active";
        }
        else {
            state = "inactive";
        }
    }
    else {
        crossing_id = "null";
        state = "null";
    }

    ui->crossingIDText->setPlainText(crossing_id);
    ui->crossingStateText->setPlainText(state);

}

void SWTrackCntrlWindow::on_uploadButton_clicked()
{
     ui->UploadPLCFrame->hide();
     ui->mainWindow->show();

}

void SWTrackCntrlWindow::on_newPLCButton_clicked()
{
    ui->UploadPLCFrame->show();
    ui->CancelButton->show();
    ui->mainWindow->hide();
}

void SWTrackCntrlWindow::on_CancelButton_clicked()
{
    if (PLCfile_present == true) {
        ui->UploadPLCFrame->hide();
        ui->mainWindow->show();
    }

}

/*void SWTrackCntrlWindow::updateInfo() {
    setWaysideInstance();
    setBlockTable();
    setSwitchTable();
}*/

void SWTrackCntrlWindow::on_toggleSwitchButton_clicked()
{
    QString old_switch_state;
    QString new_switch_state;
    QString new_switch_tail;

    if (wayside.switch_head != -1) {

    old_switch_state = ui->switchStateText->toPlainText();


    if (old_switch_state == "straight") {
        setSwitchUI(wayside, 1);
        new_switch_state = "diverging";
        setSwitchUI(wayside, true);
        new_switch_tail = QString::number(wayside.switch_tail1);
    }
    if (old_switch_state == "diverging") {
        setSwitchUI(wayside, 0);
        new_switch_state = "straight";
        setSwitchUI(wayside, false);
        new_switch_tail = QString::number(wayside.switch_tail0);
    }
    }
    else { //no switch
        new_switch_tail = "null";
        new_switch_state = "null";

    }

    ui->switchTailText->setPlainText(new_switch_tail);
    ui->switchStateText->setPlainText(new_switch_state);

}



void SWTrackCntrlWindow::on_enterWaysideButton_clicked()
{
    QString temp_wayside_id = ui->waysideIDText->toPlainText();
    int id = temp_wayside_id.toInt();
    wayside = getWaysideInstance(id);
    setBlock();
    setSwitch();
    setCrossing();
}

void SWTrackCntrlWindow::on_blockGetInfoButton_clicked()
{
    QString temp_block_id = ui->blockIDText->toPlainText();
    int id = temp_block_id.toInt();
    bool occ = wayside.blocks[id-1].block_occ;
    bool fail = wayside.blocks[id-1].block_fail;

    int occ_int = int(occ);
    int fail_int = int(fail);
    QString occ_s = QString::number(occ_int);
    QString fail_s;

    if (fail_int == 1) {
        fail_s = "Broken Rail";
    }
    else if (fail_int == 2) {
        fail_s = "Circuit Fail";
    }
    else if (fail_int == 4) {
        fail_s = "Power Fail";
    }
    else {
        fail_s = "None";
    }

    ui->occText->setPlainText(occ_s);
    ui->FailureText->setPlainText(fail_s);

}


void SWTrackCntrlWindow::on_selectFileButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open PLC Program"), " ", tr("Structured Text Files (*.ts)"));
    ui->PLCFileInput->setPlainText(file);
    filename = file.toStdString();
    PLCfile_present = true;
}

void SWTrackCntrlWindow::on_selectFileButton_2_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open PLC Program"), " ", tr("Structured Text Files (*.ts)"));
    ui->PLCFileInput_2->setPlainText(file);
    filename2 = file.toStdString();
    PLCfile_present = true;
}

void SWTrackCntrlWindow::on_toggleCrossingButton_clicked()
{
    QString old_state;
    QString new_state;

    if (wayside.crossing_id != -1) {

    old_state = ui->crossingStateText->toPlainText();


    if (old_state == "active") {
        setCrossingUI(wayside, 0);
        new_state = "inactive";
    }
    if (old_state == "inactive") {
        setCrossingUI(wayside, 1);
        new_state = "active";
    }
    }
    else { //no crossing
        new_state = "null";

    }

    ui->crossingStateText->setPlainText(new_state);
}
