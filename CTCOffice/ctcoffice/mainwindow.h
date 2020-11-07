#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "CTCDispatch.h"
#include "CTCSignals.h"
#include "CTCMode.h"

#include <QMainWindow>

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

private slots:
    void on_timeStart_userTimeChanged(const QTime &time);

    void on_comboLine_currentIndexChanged(const QString &arg1);

    void on_timeArrival_userTimeChanged(const QTime &time);

    void on_btnDispatch_clicked();

    void on_comboDestination_currentIndexChanged(const QString &arg1);

    void on_comboDestinationType_currentIndexChanged(const QString &arg1);

    void on_AutomaticButton_clicked();

    void on_ManualButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
