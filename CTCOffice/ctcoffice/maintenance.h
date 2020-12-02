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

    std::string line;
    int block;

private slots:
    void on_btnMM_clicked();

    void on_comboLine_currentIndexChanged(const QString &arg1);

    void on_comboBlocks_currentIndexChanged(const QString &arg1);

    void on_btnSendM_clicked();

private:
    Ui::maintenance *ui;
};

#endif // MAINTENANCE_H
