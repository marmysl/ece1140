#include "switchtablemodel.h"
#include "mk1_util.hpp"
#include "trackmodel_types.hpp"

SwitchTableModel::SwitchTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

enum Columns
{
    COL_BLOCK,
    COL_STATE,
    COL_LINK,
};

static const int NUM_COLUMNS = 3;
static QString columnHeaders[NUM_COLUMNS]
{
    "From Block",
    "State",
    "To Block"
};

static bool compSwitchIds( TrackModel::Switch *a, TrackModel::Switch *b )
{
    return (a->fromBlock->id) < (b->fromBlock->id);
}

static inline int getSwitchId( TrackModel::Switch *sw )
{
    return sw->fromBlock->id;
}

void SwitchTableModel::resetRoute( TrackModel::Route *route )
{
    switchList.clear();

    for( auto &kvp : route->switches )
    {
        switchList.push_back(kvp.second);
    }

    std::sort(switchList.begin(), switchList.end(), compSwitchIds);
    emit layoutChanged();
}

void SwitchTableModel::on_switchStatusUpdated( int switchId )
{
    int idx = MK1Util::binSearchOnField(&switchList, switchId, getSwitchId);
    if( idx < 0 ) return;

    emit dataChanged(index(idx, 0), index(idx, NUM_COLUMNS - 1));
}

QVariant SwitchTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( (orientation != Qt::Horizontal) || (role != Qt::DisplayRole) ) return QVariant::Invalid;
    if( section >= NUM_COLUMNS ) return QVariant::Invalid;

    return QVariant(columnHeaders[section]);
}

int SwitchTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return switchList.size();
}

int SwitchTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return NUM_COLUMNS;
}

QVariant SwitchTableModel::data(const QModelIndex &index, int role) const
{
    if( role != Qt::DisplayRole ) return QVariant::Invalid;
    if (!index.isValid()) return QVariant::Invalid;

    using vsize_t = std::vector<TrackModel::Switch *>::size_type;

    vsize_t row = static_cast<vsize_t>(index.row());
    int column = index.column();

    if( (column >= NUM_COLUMNS) || (row >= switchList.size()) ) return QVariant::Invalid;
    TrackModel::Switch *sw = switchList[row];

    switch( column )
    {
    case COL_BLOCK:
        return QVariant(sw->fromBlock->id);

    case COL_STATE:
        return QVariant((sw->direction == TrackModel::SW_DIVERGING) ? "Diverging" : "Straight");

    case COL_LINK:
        if( sw->direction == TrackModel::SW_DIVERGING )
        {
            return QVariant(sw->divergeBlock->id);
        }
        else return QVariant(sw->straightBlock->id);

    default:
        return QVariant::Invalid;
    }
}
