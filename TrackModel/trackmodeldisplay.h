#ifndef TRACKMODELDISPLAY_H
#define TRACKMODELDISPLAY_H

#include "tracklayout.hpp"
#include "blocktablemodel.h"
#include "switchtablemodel.h"
#include <QDialog>

namespace Ui {
class TrackModelDisplay;
}

namespace TrackModel { struct RouteStatus; struct StationStatus; }

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
    void notifyStationUpdated( TrackModel::Route *route, std::string stationName );

private slots:
    void on_regionComboBox_currentTextChanged(const QString &arg1);
    void on_stationSelector_currentTextChanged(const QString &arg1);
    void on_blocktableView_clicked(const QModelIndex &index);
    void on_applyFaultsButton_clicked();
    void on_applyStationPropsButton_clicked();

    void on_reloadLayoutButton_clicked();

private:
    Ui::TrackModelDisplay *ui;
    TrackModel::RouteStatus *selectedRoute;
    BlockTableModel blockTable;
    SwitchTableModel switchTable;
    TrackModel::StationStatus *selectedStation;
    TrackModel::BlockStatus *selectedBlock;

    void updateStationDisplay();
};

#endif // TRACKMODELDISPLAY_H
