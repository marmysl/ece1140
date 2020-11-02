#include <QtTest>

#include "TrackModel/tracklayout.hpp"

using namespace TrackModel;

class BlockLinkTester : public QObject
{
    Q_OBJECT

public:
    Block a = Block(1, "", 0, 0, 0);
    Block b = Block(2, "", 0, 0, 0);
    Block c = Block(3, "", 0, 0, 0);

    BlockLinkTester();
    ~BlockLinkTester();

private slots:
    void init();
    void simpleLink();
    void simpleRevLink();
    void switchLink();

    void entryDirSimple();
    void entryDirNull();
    void entryDirSwitch();
};

BlockLinkTester::BlockLinkTester()
{

}

BlockLinkTester::~BlockLinkTester()
{

}

void BlockLinkTester::init()
{
    a = Block(1, "", 0, 0, 0);
    b = Block(2, "", 0, 0, 0);
    c = Block(3, "", 0, 0, 0);
}

/*! Test two blocks linked with the same direction */
void BlockLinkTester::simpleLink()
{
    a.setLink(BLK_FORWARD, &b);
    b.setLink(BLK_REVERSE, &a);

    // test moving forward from a to b
    NextBlockData expected {&b, BLK_FORWARD};
    NextBlockData actual = a.getNextBlock(BLK_FORWARD);
    QCOMPARE(actual, expected);

    // test moving backwards from b to a
    expected = {&a, BLK_REVERSE};
    actual = b.getNextBlock(BLK_REVERSE);
    QCOMPARE(actual, expected);
}

/*! Test two blocks linked with opposite directions */
void BlockLinkTester::simpleRevLink()
{
    a.setLink(BLK_FORWARD, &b);
    b.setLink(BLK_FORWARD, &a);

    // test moving forward from a to b
    NextBlockData expected {&b, BLK_REVERSE};
    NextBlockData actual = a.getNextBlock(BLK_FORWARD);
    QCOMPARE(actual, expected);

    // test moving backwards from b to a
    expected.block = &a;
    expected.entryDir = BLK_REVERSE;
    actual = b.getNextBlock(BLK_FORWARD);
    QCOMPARE(actual, expected);
}

void BlockLinkTester::switchLink()
{
    // [A>] -> [B>]
    //      -> [<C]

    Switch s(&a, BLK_FORWARD, &b, &c); // a -> b or c
    a.setLink(BLK_FORWARD, &s);
    b.setLink(BLK_REVERSE, &a);
    c.setLink(BLK_FORWARD, &a);

    // test moving forward from a to b
    NextBlockData expected {&b, BLK_FORWARD};
    NextBlockData actual = a.getNextBlock(BLK_FORWARD);
    QCOMPARE(actual, expected);

    // test moving backwards from b to a
    expected = {&a, BLK_REVERSE};
    actual = b.getNextBlock(BLK_REVERSE);
    QCOMPARE(actual, expected);

    // test moving forwards from c to a
    expected = {&a, BLK_REVERSE};
    actual = c.getNextBlock(BLK_FORWARD);
    QCOMPARE(actual, expected);
}

void BlockLinkTester::entryDirSimple()
{
    // [A>] -> [B>] -> [C>]
    a.setLink(BLK_FORWARD, &b);
    b.setLink(BLK_REVERSE, &a);
    b.setLink(BLK_FORWARD, &c);
    c.setLink(BLK_REVERSE, &b);

    QCOMPARE(a.getEntryDir(&b), BLK_FORWARD); // a enters b forward
    QCOMPARE(b.getEntryDir(&c), BLK_FORWARD); // b enters c forward
    QCOMPARE(b.getEntryDir(&a), BLK_REVERSE); // b enters a reverse
}

void BlockLinkTester::entryDirNull()
{
    // test getEntryDir w/ block at end of line
    QCOMPARE(a.getEntryDir(&b), BLK_NODIR);
}

void BlockLinkTester::entryDirSwitch()
{

}

QTEST_APPLESS_MAIN(BlockLinkTester)

#include "tst_blocklinks.moc"
