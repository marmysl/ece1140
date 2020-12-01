#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QDialog>

namespace Ui {
class maintenance;
}

class maintenance : public QDialog
{
    Q_OBJECT

public:
    explicit maintenance(QWidget *parent = nullptr);
    ~maintenance();

    bool mm = false;

private slots:
    void on_btnMM_toggled(bool checked);

private:
    Ui::maintenance *ui;
};

#endif // MAINTENANCE_H
