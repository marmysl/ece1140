#ifndef TRACKMODELDISPLAY_H
#define TRACKMODELDISPLAY_H

#include "tracklayout.hpp"
#include "trackmodel_status.h"
#include <QMainWindow>
#include <QDialog>
#include <QLabel>

namespace Ui {
class TrackModelDisplay;
class BlockGeoDialog;
}

class BlockGeoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlockGeoDialog(QWidget *parent = nullptr);
    ~BlockGeoDialog();

    void setBlock( TrackModel::Block *block );

private:
    Ui::BlockGeoDialog *ui;
    TrackModel::Block *displayBlock;
};

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
    void on_showBlockGeoButton_clicked();
    void on_switchSelector_currentTextChanged(const QString &arg1);
    void on_applySwitchButton_clicked();

public slots:
    // status updates
    void on_blockUpdated( TrackModel::RouteStatus *sender, int blockId );

private:
    Ui::TrackModelDisplay *ui;
    TrackModel::RouteStatus *selectedRoute;
    TrackModel::StationStatus *selectedStation;
    TrackModel::BlockStatus *selectedBlock;
    TrackModel::Switch *selectedSwitch;
    BlockGeoDialog *layoutBlockDiag;

    std::vector<int> blockSelectList;

    QLabel sysTimeLabel;

    void updateStationDisplay();
    void updateSwitchDisplay();
    void updateBlockDisplay();
};

#endif // TRACKMODELDISPLAY_H
