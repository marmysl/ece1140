#ifndef TRACKMODELDISPLAY_H
#define TRACKMODELDISPLAY_H

#include "tracklayout.hpp"
#include "blocktablemodel.h"
#include <QDialog>

namespace Ui {
class TrackModelDisplay;
}

class TrackModelDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit TrackModelDisplay(QWidget *parent = nullptr);
    ~TrackModelDisplay();

    void setRegionList( std::vector<TrackModel::Route *> *routeList );
    void setRoute( TrackModel::RouteStatus *newRoute );

private slots:
    void on_regionComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::TrackModelDisplay *ui;
    TrackModel::RouteStatus *selectedRoute;
    BlockTableModel blockTable;
};

#endif // TRACKMODELDISPLAY_H
