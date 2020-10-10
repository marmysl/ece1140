#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class SerialPortDialog;
}

class SerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    QSerialPortInfo trackContPortInfo;
    QSerialPortInfo trainContPortInfo;

    explicit SerialPortDialog(QWidget *parent = nullptr);
    ~SerialPortDialog();

private slots:
    void on_buttonBox_accepted();


    void on_refreshButton_clicked();

    void on_trackPortCombo_currentIndexChanged(int index);

    void on_trainPortCombo_currentIndexChanged(int index);

private:
    Ui::SerialPortDialog *ui;
    QList<QSerialPortInfo> portList;
};

#endif // SERIALPORTDIALOG_H
