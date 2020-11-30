#ifndef HWPLCUI_H
#define HWPLCUI_H

#include "HardwarePLC.h"
#include <QDialog>
#include <QFileDialog>

namespace Ui {
class HWPLCUI;
}

class HWPLCUI : public QDialog
{
    Q_OBJECT

public:
    explicit HWPLCUI(QWidget *parent = nullptr);
    ~HWPLCUI();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::HWPLCUI *ui;
};

#endif // HWPLCUI_H
