#ifndef SWTRACKCNTRLWINDOW_H
#define SWTRACKCNTRLWINDOW_H

#include <QMainWindow>
#include <QStringBuilder>
#include <QString>
#include <QFileDialog>
//#include <QTimer>
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
    void setCrossing();
   // void toggleSwitch();
   // void updateInfo();
    bool PLCfile_present;
    std::string filename, filename2;
    //void myTimer();
    int timerID;
    //QTimer *my_timer;



private slots:
    //void receive_new_data();

    void on_uploadButton_clicked();

    void on_newPLCButton_clicked();

    void on_CancelButton_clicked();

    void on_toggleSwitchButton_clicked();

    void on_enterWaysideButton_clicked();

    void on_blockGetInfoButton_clicked();

    void on_selectFileButton_clicked();

    void on_selectFileButton_2_clicked();

    void on_toggleCrossingButton_clicked();

private:
    Ui::SWTrackCntrlWindow *ui;

protected:
    void timerEvent(QTimerEvent *event) override;

};



#endif // SWTRACKCNTRLWINDOW_H
