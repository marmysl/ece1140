#ifndef SYTEMWINDOW_H
#define SYSTEMWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SystemWindow; }
QT_END_NAMESPACE

class SystemWindow : public QMainWindow
{
    Q_OBJECT

public:
    SystemWindow(QWidget *parent = nullptr);
    ~SystemWindow();

private:
    Ui::SystemWindow *ui;
};
#endif // SYSTEMWINDOW_H
