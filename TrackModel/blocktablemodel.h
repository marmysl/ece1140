#ifndef BLOCKTABLEMODEL_H
#define BLOCKTABLEMODEL_H

#include <QAbstractTableModel>

#include "trackmodel_status.h"

class BlockTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Columns
    {
        COL_ID,
        COL_SECTION,
        COL_LENGTH,
        COL_GRADE,
        COL_LIMIT,
        COL_ONEWAY,
        COL_TUNNEL,
        COL_RSIG,
        COL_OCCUPIED,
        COL_FSIG,
        COL_FAULTS,
        COL_SPEED,
        COL_AUTH,
        COL_STATION,
    };

    explicit BlockTableModel(QObject *parent = nullptr);

    // Data manip:
    void resetRoute( TrackModel::RouteStatus *route );
    void on_blockStatusUpdated( int blockId );
    TrackModel::BlockStatus *getBlockAtIdx( int idx );

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<TrackModel::BlockStatus *> blockList = std::vector<TrackModel::BlockStatus *>();
};

#endif // BLOCKTABLEMODEL_H
