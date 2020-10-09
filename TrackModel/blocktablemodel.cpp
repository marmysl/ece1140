#include "blocktablemodel.h"
#include "trackmodel_main.hpp"

BlockTableModel::BlockTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

static const int NUM_COLUMNS = 8;
enum Columns
{
    COL_ID = 0,
    COL_SECTION = 1,
    COL_LENGTH = 2,
    COL_GRADE = 3,
    COL_LIMIT = 4,
    COL_OCCUPIED = 5,
    COL_SPEED = 6,
    COL_AUTH = 7,
};

static QString columnHeaders[] {
    "Block Id",
    "Section",
    "Length (m)",
    "Grade",
    "Speed Limit (kph)",
    "Occupied",
    "Speed Cmd",
    "Auth Cmd"
};

static bool compBlockIds( TrackModel::BlockStatus *a, TrackModel::BlockStatus *b ) {
    return (a->layoutBlock->id) < (b->layoutBlock->id);
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
    if( role != Qt::DisplayRole ) return QVariant();

    if (!index.isValid()) return QVariant::Invalid;

    using vsize_t = std::vector<TrackModel::BlockStatus *>::size_type;

    vsize_t row = static_cast<vsize_t>(index.row());
    vsize_t column = static_cast<vsize_t>(index.column());

    if( (column >= NUM_COLUMNS) || (row >= blockList.size()) ) return QVariant::Invalid;
    TrackModel::BlockStatus *block = blockList[row];

    switch( column )
    {
    case COL_ID:
        return QVariant(block->layoutBlock->id);

    case COL_SECTION:
        return QVariant(QString::fromStdString(block->layoutBlock->section));

    case COL_LENGTH:
        return QVariant(block->layoutBlock->length);

    case COL_GRADE:
        return QVariant(QString("%1%").arg(block->layoutBlock->grade * 100));

    case COL_LIMIT:
        return QVariant(block->layoutBlock->speedLimit);

    case COL_OCCUPIED:
        return QVariant((block->isOccupied()) ? "Yes" : "No");

    case COL_SPEED:
        return QVariant(block->circuit.decodeSpeed());

    case COL_AUTH:
        return QVariant(block->circuit.decodeAuthority());

    default:
        return QVariant::Invalid;
    }
}
