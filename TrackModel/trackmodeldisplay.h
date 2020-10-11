#ifndef TRACKMODELDISPLAY_H
#define TRACKMODELDISPLAY_H

#include "tracklayout.hpp"
#include "blocktablemodel.h"
#include "switchtablemodel.h"
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
    void notifyBlockUpdated( TrackModel::RouteStatus *route, int blockId );
    void notifySwitchUpdated( TrackModel::Route *route, int switchId );

private slots:
    void on_regionComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::TrackModelDisplay *ui;
    TrackModel::RouteStatus *selectedRoute;
    BlockTableModel blockTable;
    SwitchTableModel switchTable;
};

#endif // TRACKMODELDISPLAY_H
