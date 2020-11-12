#ifndef SWTRACKCNTRLWINDOW_H
#define SWTRACKCNTRLWINDOW_H

#include <QMainWindow>
#include <QStringBuilder>
#include <QString>
#include <QFileDialog>
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
    std::string filename;



private slots:
    void on_uploadButton_clicked();

    void on_newPLCButton_clicked();

    void on_CancelButton_clicked();

    void on_toggleSwitchButton_clicked();

    void on_enterWaysideButton_clicked();

    void on_blockGetInfoButton_clicked();

    void on_selectFileButton_clicked();

private:
    Ui::SWTrackCntrlWindow *ui;
    int timerID;
    int count;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // SWTRACKCNTRLWINDOW_H
