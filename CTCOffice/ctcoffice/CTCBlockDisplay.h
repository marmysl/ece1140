#pragma once

#include "TrackModel/trackmodel_status.h"
#include <QWidget>
#include <QColor>
#include "CTCBlockStatus.h"

using namespace TrackModel;

class CTCBlockDisplay : public QWidget
{
    Q_OBJECT

    //representation of each element on the map
    struct BlockRepr
    {
        int left;
        int top;
        BlockDir orient;
        CTCBlockStatus *stat;

        BlockRepr() :
            left(0), top(0), orient(BLK_FORWARD), stat(nullptr) {}

        BlockRepr( int l, int t, BlockDir dir, CTCBlockStatus *blk ) :
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

    explicit CTCBlockDisplay(QWidget *parent = nullptr);

    void setRoute( CTCRouteStatus *route );

private:
    const QColor UNNOCC_COLOR = {140, 190, 120};
    const QColor OCC_COLOR = {200, 40, 30};
    const QColor YARD_COLOR = {80, 110, 180};

    const QColor LINK_COLOR = {230, 230, 230};
    const QColor NOLINK_COLOR = {60, 60, 60};
    const QColor SWITCH_ACTIVE_COLOR = {255, 230, 0};

    const QColor STATION_COLOR = {80, 110, 180};
    const QColor FAULT_COLOR = {255, 20, 0};

    const QColor SIG_GREEN = {30, 180, 30};
    const QColor SIG_YELLOW = {210, 200, 30};
    const QColor SIG_RED = {180, 10, 0};

    CTCRouteStatus *route;
    std::unordered_map<int, BlockRepr> blocks;
    std::unordered_map<int, SwitchRepr> switches;
    std::vector<LinkRepr> links;

protected:
    void drawBlock( BlockRepr&, QPainter* );
    void drawSignals( BlockRepr&, QPainter* );
    void drawSwitch( SwitchRepr&, QPainter* );
    void drawCrossbuck( BlockRepr&, QPainter* );
    void paintEvent( QPaintEvent * );

};
