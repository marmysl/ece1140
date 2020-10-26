#include "systemsettingsdialog.h"
#include "ui_systemsettingsdialog.h"

#include "timetracker.h"
#include "weatherstation.h"
#include "system_main.h"

SystemSettingsDialog::SystemSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemSettingsDialog)
{
    ui->setupUi(this);
    ui->newTimeInput->setDateTime(QDateTime::currentDateTime());

    connect(systemClock, &TimeTracker::timeAdvanced, this, &SystemSettingsDialog::on_timeAdvanced);
    connect(weather, &WeatherStation::tempChanged, this, &SystemSettingsDialog::on_tempChanged);
}

SystemSettingsDialog::~SystemSettingsDialog()
{
    delete ui;
}

void SystemSettingsDialog::on_quitButton_clicked()
{
    mk1_app->quit();
}

void SystemSettingsDialog::on_applyTimeButton_clicked()
{
    QDateTime newTime = ui->newTimeInput->dateTime();
    systemClock->changeTime(newTime);
}

void SystemSettingsDialog::on_applyClockPropsButton_clicked()
{
    int res = ui->resolutionInput->value();
    systemClock->setResolution(res);

    float speed = ui->speedInput->value();
    systemClock->timeScale = speed;
}

void SystemSettingsDialog::on_pauseButton_clicked()
{
    systemClock->pause();
}

void SystemSettingsDialog::on_playButton_clicked()
{
    systemClock->play();
}


void SystemSettingsDialog::on_forceTempCheck_stateChanged(int arg1)
{
    if( arg1 == Qt::Checked )
    {
        weather->forceTempF(ui->manualTempInput->value());
    }
    else
    {
        weather->stopForcingTemp();
    }
}

// slots
void SystemSettingsDialog::on_timeAdvanced( QDateTime newTime )
{
    ui->curTimeLabel->setText(newTime.toString());
}

void SystemSettingsDialog::on_tempChanged()
{
    ui->curTempLabel->setText(QString::fromStdString(weather->getTempFString()));
}
