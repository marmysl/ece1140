#ifndef TICKETSDIALOG_H
#define TICKETSDIALOG_H

#include <QDialog>

namespace Ui {
class TicketsDialog;
}

class TicketsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TicketsDialog(QWidget *parent = nullptr);
    ~TicketsDialog();

private:
    Ui::TicketsDialog *ui;
};

#endif // TICKETSDIALOG_H
