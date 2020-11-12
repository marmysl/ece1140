#ifndef SWTRACKCNTRLWINDOW_H
#define SWTRACKCNTRLWINDOW_H

#include <QMainWindow>
#include <QStringBuilder>
#include "TrackController.h"
#include "trackcntrl_main.h"

namespace Ui {
class SWTrackCntrlWindow;
}

class SWTrackCntrlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SWTrackCntrlWindow(QWidget *parent = nullptr);
    ~SWTrackCntrlWindow();
    TrackController wayside;
    bool setPLC();
    void setBlock();
    void setSwitch();
   // void toggleSwitch();
   // void updateInfo();
    bool PLCfile_present;


private slots:
    void on_uploadButton_clicked();

    void on_newPLCButton_clicked();

    void on_CancelButton_clicked();

    void on_toggleSwitchButton_clicked();

    void on_enterWaysideButton_clicked();

    void on_blockGetInfoButton_clicked();

private:
    Ui::SWTrackCntrlWindow *ui;
};

#endif // SWTRACKCNTRLWINDOW_H
