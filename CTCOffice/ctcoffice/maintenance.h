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

private:
    Ui::maintenance *ui;
};

#endif // MAINTENANCE_H
