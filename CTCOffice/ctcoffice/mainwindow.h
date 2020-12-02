#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "CTCDispatch.h"
#include "../../SWTrackController/CTCSignals.h"
#include "schedule.h"
#include "maintenance.h"
#include "throughput.h"
#include "Files.h"

#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    CTCDispatch ctc;
    CTCMode m;
    schedule *autoSchedule;
    maintenance *maint = new maintenance(this);
    throughput *th;
    Files *map = new Files(this);

    int timerID;
    int count = 0;

public slots:
    void updateRoute();
private slots:
    void on_timeStart_userTimeChanged(const QTime &time);

    void on_comboLine_currentIndexChanged(const QString &arg1);

    void on_timeArrival_userTimeChanged(const QTime &time);

    void on_btnDispatch_clicked();

    void on_comboDestination_currentIndexChanged(const QString &arg1);

    void on_comboDestinationType_currentIndexChanged(const QString &arg1);

    void on_AutomaticButton_clicked();

    void on_ManualButton_clicked();

    void on_btnMap_clicked();

    void on_comboDisplayLine_currentIndexChanged(const QString &arg1);

    void on_btnSchedule_clicked();

    void on_btnMaintenance_clicked();

    void on_comboDisplayBlock_currentIndexChanged(const QString &arg1);

    void on_btnThroughput_clicked();

private:
    Ui::MainWindow *ui;

protected:
    void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H
