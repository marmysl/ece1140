#ifndef SWITCHTABLEMODEL_H
#define SWITCHTABLEMODEL_H

#include "tracklayout.hpp"
#include <QAbstractTableModel>

class SwitchTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit SwitchTableModel(QObject *parent = nullptr);

    // Data manip:
    void resetRoute( TrackModel::Route *route );
    void on_switchStatusUpdated( int switchId );

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<TrackModel::Switch *> switchList;
};

#endif // SWITCHTABLEMODEL_H
