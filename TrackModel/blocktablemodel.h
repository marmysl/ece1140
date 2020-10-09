#ifndef BLOCKTABLEMODEL_H
#define BLOCKTABLEMODEL_H

#include <QAbstractTableModel>

namespace TrackModel
{
    struct RouteStatus;
    struct BlockStatus;
}

class BlockTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit BlockTableModel(QObject *parent = nullptr);

    // Data manip:
    void resetRoute( TrackModel::RouteStatus *route );

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
