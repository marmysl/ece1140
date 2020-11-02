#ifndef SYSTEMSETTINGSDIALOG_H
#define SYSTEMSETTINGSDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class SystemSettingsDialog;
}

class SystemSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SystemSettingsDialog(QWidget *parent = nullptr);
    ~SystemSettingsDialog();

private slots:
    void on_quitButton_clicked();
    void on_applyTimeButton_clicked();
    void on_applyClockPropsButton_clicked();
    void on_pauseButton_clicked();
    void on_playButton_clicked();
    void on_forceTempCheck_stateChanged(int arg1);

    void on_timeAdvanced( QDateTime newTime );
    void on_tempChanged();

private:
    Ui::SystemSettingsDialog *ui;
};

#endif // SYSTEMSETTINGSDIALOG_H
