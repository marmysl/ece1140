#include "binaryindicator.h"
#include <QPainter>

BinaryIndicator::BinaryIndicator(QWidget *parent) : QWidget(parent)
{
    value = false;
}

void BinaryIndicator::setValue(bool newVal)
{
    if( value != newVal )
    {
        value = newVal;
        update();
    }
}

void BinaryIndicator::paintEvent( QPaintEvent *event )
{
    QPainter painter(this);

    if( value )
    {
        painter.fillRect(rect(), QBrush(TRUE_COLOR));
    }
    else
    {
        painter.fillRect(rect(), QBrush(FALSE_COLOR));
    }
}
