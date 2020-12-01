#ifndef HWPLCUI_H
#define HWPLCUI_H

#include <QDialog>
#include <QFileDialog>

#include "HWTrackController_main.h"

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


    void on_greenButton_clicked();

    void on_redButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::HWPLCUI *ui;
    QString glfilename;
    QString rlfilename;
};

#endif // HWPLCUI_H
