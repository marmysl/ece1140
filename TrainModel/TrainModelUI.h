#ifndef TRAINMODELUI_H
#define TRAINMODELUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TrainModelUI; }
QT_END_NAMESPACE

class TrainModelUI : public QMainWindow
{
    Q_OBJECT

public:
    TrainModelUI(QWidget *parent = nullptr);
    ~TrainModelUI();
    //void updatePower(double power);

private:
    Ui::TrainModelUI *ui;
};
#endif // TRAINMODELUI_H
