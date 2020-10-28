#include "blocktablemodel.h"
#include "trackmodel_main.hpp"
#include "mk1_util.hpp"

BlockTableModel::BlockTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

enum Columns
{
    COL_ID,
    COL_SECTION,
    COL_LENGTH,
    COL_GRADE,
    COL_LIMIT,
    COL_ONEWAY,
    COL_TUNNEL,
    COL_OCCUPIED,
    COL_FAULTS,
    COL_SPEED,
    COL_AUTH,
};

static const int NUM_COLUMNS = 11;

static QString columnHeaders[NUM_COLUMNS]
{
    "Block Id",
    "Section",
    "Length",
    "Grade",
    "Speed Limit",
    "Oneway",
    "Tunnel",
    "Occupied",
    "Faults",
    "Speed Cmd",
    "Auth Cmd"
};

static bool compBlockIds( TrackModel::BlockStatus *a, TrackModel::BlockStatus *b ) {
    return (a->layoutBlock->id) < (b->layoutBlock->id);
}

static inline int getBlockId( TrackModel::BlockStatus *blk )
{
    return blk->layoutBlock->id;
}

void BlockTableModel::resetRoute( TrackModel::RouteStatus *route )
{
    std::vector<TrackModel::BlockStatus *>().swap(blockList);

    for( auto &kvp : route->blockMap )
    {
        blockList.push_back(kvp.second);
    }

    std::sort(blockList.begin(), blockList.end(), compBlockIds);

    emit layoutChanged();
}

void BlockTableModel::on_blockStatusUpdated( int blockId )
{
    int idx = MK1Util::binSearchOnField(&blockList, blockId, getBlockId);
    if( idx < 0 ) return;

    emit dataChanged(index(idx, 0), index(idx, NUM_COLUMNS - 1));
}

TrackModel::BlockStatus *BlockTableModel::getBlockAtIdx( int idx )
{
    if( (idx < 0) || (static_cast<uint>(idx) > blockList.size()) ) return NULL;

    return blockList[idx];
}


QVariant BlockTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( (orientation != Qt::Horizontal) || (role != Qt::DisplayRole) ) return QVariant();
    if( section >= NUM_COLUMNS ) return QVariant::Invalid;

    return QVariant(columnHeaders[section]);
}

int BlockTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return blockList.size();
}

int BlockTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return NUM_COLUMNS;
}

QVariant BlockTableModel::data(const QModelIndex &index, int role) const
{
    using vsize_t = std::vector<TrackModel::BlockStatus *>::size_type;

    if (!index.isValid()) return QVariant::Invalid;

    vsize_t row = static_cast<vsize_t>(index.row());
    vsize_t column = static_cast<vsize_t>(index.column());

    if( (column >= NUM_COLUMNS) || (row >= blockList.size()) ) return QVariant::Invalid;
    TrackModel::BlockStatus *block = blockList[row];

    if( role == Qt::BackgroundRole )
    {
        if( column == COL_OCCUPIED )
        {
            return (block->isOccupied()) ? QBrush(QColor(255, 160, 160)) : QBrush(QColor(160, 255, 160));
        }
        else return QVariant::Invalid;
    }
    else if( role != Qt::DisplayRole ) return QVariant::Invalid;


    switch( column )
    {
    case COL_ID:
        return QVariant(block->layoutBlock->id);

    case COL_SECTION:
        return QString::fromStdString(block->layoutBlock->section);

    case COL_LENGTH:
        return QString("%1 m").arg(block->layoutBlock->length);

    case COL_GRADE:
        return QString("%1%").arg(block->layoutBlock->grade * 100);

    case COL_LIMIT:
        return QString("%1 kph").arg(block->layoutBlock->speedLimit);

    case COL_ONEWAY:
        if( block->layoutBlock->oneWay == TrackModel::BLK_FORWARD ) return QVariant("FWD");
        else if( block->layoutBlock->oneWay == TrackModel::BLK_REVERSE ) return QVariant("REV");
        else return QVariant();

    case COL_TUNNEL:
        return QVariant((block->layoutBlock->underground) ? "Yes" : "");

    case COL_OCCUPIED:
        return QVariant((block->isOccupied()) ? "Yes" : "No");

    case COL_FAULTS:
        return TrackModel::getFaultString(block->faults);

    case COL_SPEED:
        return QVariant(block->getCircuitData().decodeSpeed());

    case COL_AUTH:
        return QVariant(block->getCircuitData().decodeAuthority());

    default:
        return QVariant::Invalid;
    }
}
