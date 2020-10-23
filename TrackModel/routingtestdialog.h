#ifndef ROUTINGTESTDIALOG_H
#define ROUTINGTESTDIALOG_H

#include "tracklayout.hpp"
#include "trackrouter.h"

#include <QDialog>

namespace Ui {
class RoutingTestDialog;
}

class RoutingTestDialog : public QDialog
{
    Q_OBJECT

public:
    TrackModel::Route *route;
    TrackModel::TrackRouter *router;
    int *blockList;

    explicit RoutingTestDialog(TrackModel::Route *route, QWidget *parent = nullptr);
    ~RoutingTestDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RoutingTestDialog *ui;
};

#endif // ROUTINGTESTDIALOG_H
