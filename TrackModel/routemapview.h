#pragma once

#include "trackmodel_status.h"
#include <QWidget>
#include <QColor>

using namespace TrackModel;

class RouteMapView : public QWidget
{
    Q_OBJECT

    struct BlockRepr
    {
        int left;
        int top;
        BlockDir orient;
        BlockStatus *stat;

        BlockRepr( int l, int t, BlockDir dir, BlockStatus *blk ) :
            left(l), top(t), orient(dir), stat(blk) {}
    };

    struct SwitchRepr
    {
        QPoint start;
        QPoint straightEnd;
        QPoint divEnd;

        Switch *stat;

        SwitchRepr( QPoint start, Switch *sw ) :
            start(start), straightEnd(start), divEnd(start), stat(sw) {}
    };

    struct LinkRepr
    {
        int startX;
        int startY;
        int endX;
        int endY;

        LinkRepr( int x1, int y1, int x2, int y2 ) :
            startX(x1), startY(y1), endX(x2), endY(y2) {}
    };

public:
    static const int BLOCK_LENGTH = 60;
    static const int BLOCK_THICKNESS = 6;
    static const int LINK_WIDTH = BLOCK_LENGTH / 2;
    static const int LINK_THICK = BLOCK_THICKNESS / 2;
    static const int ROW_OFFSET = 50;

    explicit RouteMapView(QWidget *parent = nullptr);

    void setRoute( RouteStatus *route );

private:
    const QColor UNNOCC_COLOR = {120, 255, 100};
    const QColor OCC_COLOR = {255, 20, 0};
    const QColor YARD_COLOR = {200, 0, 200};

    const QColor LINK_COLOR = {230, 230, 230};
    const QColor NOLINK_COLOR = {60, 60, 60};
    const QColor SWITCH_ACTIVE_COLOR = {255, 230, 0};

    const QColor STATION_COLOR = {80, 100, 230};
    const QColor FAULT_COLOR = {255, 20, 0};

    RouteStatus *route;
    BlockStatus yardStat;
    std::unordered_map<int, BlockRepr> blocks;
    std::unordered_map<int, SwitchRepr> switches;
    std::vector<LinkRepr> links;

protected:
    void drawBlock( BlockRepr&, QPainter* );
    void drawSwitch( SwitchRepr&, QPainter* );
    void paintEvent( QPaintEvent * );

signals:

};
