#include "signalindicator.h"
#include <QPainter>

SignalIndicator::SignalIndicator(QWidget *parent) : QStyledItemDelegate(parent)
{
}

void SignalIndicator::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QColor r = RED_OFF;
    QColor y = YELLOW_OFF;
    QColor g = GREEN_OFF;

    int state;
    QVariant v = index.model()->data(index, Qt::DisplayRole);
    if( !v.isValid() ) return;
    state = v.toInt();

    switch( state )
    {
    case 0:
        r = RED_ON;
        break;

    case 1:
        y = YELLOW_ON;
        break;

    case 2:
        g = GREEN_ON;
        break;
    }

    painter->save();

    painter->fillRect(redArea(option.rect), QBrush(r));
    painter->fillRect(yellowArea(option.rect), QBrush(y));
    painter->fillRect(greenArea(option.rect), QBrush(g));

    painter->restore();
}

QRect SignalIndicator::redArea( const QRect a ) const
{
    return QRect(a.left(), a.top(), a.width() / 3, a.height());
}

QRect SignalIndicator::yellowArea( const QRect a ) const
{
    int w = a.width() / 3;
    return QRect(a.left() + w, a.top(), w, a.height());
}

QRect SignalIndicator::greenArea( const QRect a ) const
{
    int w = a.width() - ((a.width() / 3) * 2);
    return QRect(a.right() - w, a.top(), w, a.height());
}
