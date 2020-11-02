#ifndef TRACKMODELDISPLAY_H
#define TRACKMODELDISPLAY_H

#include "tracklayout.hpp"
#include "trackmodel_status.h"
#include "signalindicator.h"
#include <QMainWindow>
#include <QLabel>

namespace Ui {
class TrackModelDisplay;
}

class TrackModelDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrackModelDisplay(QWidget *parent = nullptr);
    ~TrackModelDisplay();

    void setRegionList( std::vector<TrackModel::Route *> *routeList );
    void setRoute( TrackModel::RouteStatus *newRoute );
    void notifySwitchUpdated( TrackModel::Route *route, int switchId );
    void notifyStationUpdated( TrackModel::Route *route, std::string stationName );

private slots:
    void on_regionComboBox_currentTextChanged(const QString &arg1);
    void on_stationSelector_currentTextChanged(const QString &arg1);
    void on_blockSelector_currentIndexChanged(int index);
    void on_applyFaultsButton_clicked();
    void on_applyStationPropsButton_clicked();
    void on_clearPlatformButton_clicked();
    void on_reloadLayoutButton_clicked();
    void on_testRouteButton_clicked();
    void on_timeAdvanced( const QDateTime &newTime, qint64 delta );
    void on_applySignalButton_clicked();
    void on_displayTicketsButton_clicked();

public slots:
    // status updates
    void on_block_updated( TrackModel::RouteStatus *sender, int blockId );

private:
    Ui::TrackModelDisplay *ui;
    TrackModel::RouteStatus *selectedRoute;
    SignalIndicator *sigIndicatorDelegate;
    TrackModel::StationStatus *selectedStation;
    TrackModel::BlockStatus *selectedBlock;

    std::vector<int> blockSelectList;

    QLabel sysTimeLabel;

    void updateStationDisplay();
};

#endif // TRACKMODELDISPLAY_H
