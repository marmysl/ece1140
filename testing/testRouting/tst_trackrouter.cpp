#include <QtTest>
#include <QObject>

#include "TrackModel/trackrouter.h"

using namespace TrackModel;

class TrackRouterTester : public QObject
{
    Q_OBJECT

public:
    TrackRouterTester();
    ~TrackRouterTester();

private slots:
    void routeSingle();
    void routeSwitch();
    void routeOnewayLoop();
    void routeBacktrack();
};

TrackRouterTester::TrackRouterTester() {}

TrackRouterTester::~TrackRouterTester() {}

void TrackRouterTester::routeSingle()
{
    Block a(1, "", 10, 0, 0);
    Block b(2, "", 10, 0, 0);

    a.setLink(BLK_FORWARD, &b);
    b.setLink(BLK_REVERSE, &a);

    Route r("Single");
    r.blocks.insert({1, &a});
    r.blocks.insert({2, &b});

    TrackRouter router(&r);

    TrainPathInfo path = router.findPath(1, BLK_NODIR, 2);

    auto &blockList = path.blocks;
    QCOMPARE(blockList.size(), 2);

    QCOMPARE(blockList[0], &a);
    QCOMPARE(blockList[1], &b);
}

void TrackRouterTester::routeSwitch()
{
    // [A>] -> [B>]
    //      -> [<C]

    Block a(1, "", 10, 0, 0);
    Block b(2, "", 10, 0, 0);
    Block c(3, "", 10, 0, 0);

    Switch s(&a, BLK_FORWARD, &b, &c);
    a.setLink(BLK_FORWARD, &s);
    b.setLink(BLK_REVERSE, &a);
    c.setLink(BLK_FORWARD, &a);

    Route r("Switch");
    r.blocks.insert({1, &a});
    r.blocks.insert({2, &b});
    r.blocks.insert({3, &c});

    TrackRouter router(&r);

    // test 1 to 2
    TrainPathInfo path = router.findPath(1, BLK_NODIR, 2);

    // expected: A -> B, s straight
    std::vector<Block *> expectedBlocks {&a, &b};
    auto &switchList = path.switchStates;

    QCOMPARE(path.blocks, expectedBlocks);

    std::pair<int, SwitchState> expectedSwitch(1, SW_STRAIGHT);
    QCOMPARE(switchList.size(), 1);
    QCOMPARE(switchList[0], expectedSwitch);

    // test 1 to 3
    path = router.findPath(1, BLK_NODIR, 3);

    // expected: A -> C, s diverge
    expectedBlocks[1] = &c;
    switchList = path.switchStates;

    QCOMPARE(path.blocks, expectedBlocks);

    expectedSwitch.second = SW_DIVERGING;
    QCOMPARE(switchList.size(), 1);
    QCOMPARE(switchList[0], expectedSwitch);
}

void TrackRouterTester::routeOnewayLoop()
{
    // [A>] -> [B>] -> [C>] -v
    //   ^---- [<E] <- [<D] <-

    Block a(1, "", 10, 0, 0);
    Block b(2, "", 10, 0, 0, BLK_FORWARD);
    Block c(3, "", 10, 0, 0, BLK_FORWARD);
    Block d(4, "", 10, 0, 0, BLK_FORWARD);
    Block e(5, "", 10, 0, 0, BLK_FORWARD);

    Switch s(&a, BLK_FORWARD, &b, &e);
    a.setLink(BLK_FORWARD, &s);
    b.setLink(BLK_REVERSE, &a); b.setLink(BLK_FORWARD, &c);
    c.setLink(BLK_REVERSE, &b); c.setLink(BLK_FORWARD, &d);
    d.setLink(BLK_REVERSE, &c); d.setLink(BLK_FORWARD, &e);
    e.setLink(BLK_REVERSE, &d); e.setLink(BLK_FORWARD, &a);

    Route r("Loopy");
    r.blocks.insert({1, &a});
    r.blocks.insert({2, &b});
    r.blocks.insert({3, &c});
    r.blocks.insert({4, &d});
    r.blocks.insert({5, &e});

    TrackRouter router(&r);

    // test 1 to 5
    TrainPathInfo path = router.findPath(1, BLK_NODIR, 5);

    // expected: A > B > C > D > E, sw1 straight
    // path needs to follow the long route to obey the oneway restriction
    std::vector<Block *> expectedBlocks {&a, &b, &c, &d, &e};
    QCOMPARE(path.blocks, expectedBlocks);

    auto &switchList = path.switchStates;
    std::pair<int, SwitchState> expectedSwitch(1, SW_STRAIGHT);
    QCOMPARE(switchList.size(), 1);
    QCOMPARE(switchList[0], expectedSwitch);

    // test 2 to 1
    path = router.findPath(2, BLK_NODIR, 1);

    // expected: B > C > D > E > A
    // path needs to follow the long route to obey oneway
    expectedBlocks = std::vector<Block *> {&b, &c, &d, &e, &a};
    QCOMPARE(path.blocks, expectedBlocks);
}

void TrackRouterTester::routeBacktrack()
{
    // [A>] -> [B>] -> [C>] -> [D>] -v
    // [<F] <-              <- [<E]

    Block a(1, "", 10, 0, 0);
    Block b(2, "", 10, 0, 0);
    Block c(3, "", 10, 0, 0);
    Block d(4, "", 10, 0, 0, BLK_FORWARD);
    Block e(5, "", 10, 0, 0, BLK_FORWARD);
    Block f(6, "", 10, 0, 0);

    Switch s2(&b, BLK_REVERSE, &f, &a);
    Switch s3(&c, BLK_FORWARD, &d, &e);

    a.setLink(BLK_FORWARD, &b);
    b.setLink(BLK_REVERSE, &s2); b.setLink(BLK_FORWARD, &c);
    c.setLink(BLK_REVERSE, &b); c.setLink(BLK_FORWARD, &s3);
    d.setLink(BLK_REVERSE, &c); d.setLink(BLK_FORWARD, &e);
    e.setLink(BLK_REVERSE, &d); e.setLink(BLK_FORWARD, &c);
    f.setLink(BLK_REVERSE, &b);

    Route r("Backtracker");
    r.blocks.insert({1, &a});
    r.blocks.insert({2, &b});
    r.blocks.insert({3, &c});
    r.blocks.insert({4, &d});
    r.blocks.insert({5, &e});
    r.blocks.insert({6, &f});

    TrackRouter router(&r);

    // test 1 to 6 (A to F), need to go out, around loop and back
    TrainPathInfo path = router.findPath(1, BLK_NODIR, 6);

    // expected: A > B > C > D > E > C > B > F, sw2 (B) straight, sw3 (C) straight
    // path needs to follow the long route to obey the oneway restriction
    std::vector<Block *> expectedBlocks {&a, &b, &c, &d, &e, &c, &b, &f};
    QCOMPARE(path.blocks, expectedBlocks);

    auto &switchList = path.switchStates;
    std::pair<int, SwitchState> expectedS2(2, SW_STRAIGHT);
    std::pair<int, SwitchState> expectedS3(3, SW_STRAIGHT);
    QCOMPARE(switchList.size(), 2);
    QCOMPARE(switchList[0], expectedS3);
    QCOMPARE(switchList[1], expectedS2);
}

QTEST_APPLESS_MAIN(TrackRouterTester)

#include "tst_trackrouter.moc"
