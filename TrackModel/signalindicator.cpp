#include "signalindicator.h"
#include <QPainter>
#include <algorithm>

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

    painter->fillRect(option.rect, QColor(40, 40, 40));

    painter->setBrush(r);
    painter->drawEllipse(redArea(option.rect));

    painter->setBrush(y);
    painter->drawEllipse(yellowArea(option.rect));

    painter->setBrush(g);
    painter->drawEllipse(greenArea(option.rect));

    painter->restore();
}

QRect SignalIndicator::redArea( const QRect a ) const
{
    int dim = std::min(a.width() / 3, a.height());
    int xCent = a.width() / 6;

    int left = a.left() + xCent - (dim / 2);
    int top = a.top() + (a.height() / 2) - (dim / 2);

    return QRect(left, top, dim, dim);
}

QRect SignalIndicator::yellowArea( const QRect a ) const
{
    int dim = std::min(a.width() / 3, a.height());
    int xCent = a.width() / 2;

    int left = a.left() + xCent - (dim / 2);
    int top = a.top() + (a.height() / 2) - (dim / 2);

    return QRect(left, top, dim, dim);
}

QRect SignalIndicator::greenArea( const QRect a ) const
{
    int dim = std::min(a.width() / 3, a.height());
    int xCent = a.width() - (a.width() / 6);

    int left = a.left() + xCent - (dim / 2);
    int top = a.top() + (a.height() / 2) - (dim / 2);

    return QRect(left, top, dim, dim);
}
