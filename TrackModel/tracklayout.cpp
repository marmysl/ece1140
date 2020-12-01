#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "tracklayout.hpp"
#include "mk1_util.hpp"

#include <QFileInfo>

using namespace TrackModel;
using namespace MK1Util;

std::vector<Route *> TrackModel::routes = std::vector<Route *>();

Route *TrackModel::getRoute( std::string name ) {
    for( Route *r : routes ) {
        if( !name.compare(r->name) ) {
            return r;
        }
    }

    return nullptr;
}

// Route Members
Route::Route( std::string name ) :
    name(name), displayStartBlk(-1), displayStartDir(BLK_FORWARD) {}

void Route::loadLayout( std::string fileName ) {
    std::ifstream layoutFile;

    QFileInfo lfInfo(QString::fromStdString(fileName));
    layoutFile.open(lfInfo.absoluteFilePath().toStdString(), std::ios::in);

    if( !layoutFile.is_open() ) throw std::invalid_argument ("Unable to open layout file");

    std::string nextLine;
    std::stringstream buf = std::stringstream ();

    // oh boy a parser
    enum ParseState {
        LL_SECTION, LL_ID, LL_LEN, LL_GRADE, LL_SPEED, LL_ONEWAY, LL_TAGS,
        LL_PREV_BLK, LL_NEXT_BLK, LL_BRANCH_A, LL_BRANCH_B, LL_STATION
    };

    const char *stateNames[] {
        "Section", "BlockId", "Length", "Grade", "Speed Limit", "One Way", "Tags",
        "Prev Block", "Next Block", "Branch Rev", "Branch Fwd", "Station"
    };

    const int TUNNEL_FLAG = 1;
    const int CROSSING_FLAG = 2;

    // getline() <-------------------------------------------------------------------------------------------
    //   |                                                                                                   |
    //   v                                                                                                   |
    // section -> id -> len -> grade -> speed -> oneway -> tags -> prev -> next -> branchA -> branchB -> station

    struct LinkInfo {
        int prevStraight;
        int nextStraight;

        int prevDiverge;
        int nextDiverge;

        Block *srcBlock;

        LinkInfo( Block *src, int prev, int next, int pDiv, int nDiv ) :
            prevStraight(prev), nextStraight(next), prevDiverge(pDiv), nextDiverge(nDiv), srcBlock(src) {}

        inline bool nonNull()
        {
            return (prevStraight >= 0) || (nextStraight >= 0) || (prevDiverge >= 0) || (nextDiverge >= 0);
        }
    };

    ParseState state;
    int fileLine = 1;

    std::vector<LinkInfo> voidLinks = std::vector<LinkInfo> ();
    int parsedStartBlockId = -1;
    BlockDir parsedStartDir = BLK_FORWARD;

    std::string sectionName;
    int blockNum;
    float length;
    float grade;
    float speedLimit;
    BlockDir oneway;

    int blkRev, blkFwd;
    int branchRev;
    int branchFwd;
    std::string station;
    bool isTunnel;
    bool hasCrossing;

    // for each line of the config file
    while( getline(layoutFile, nextLine) ) {

        // check if line is commented
        if( (nextLine.length() == 0) || (nextLine.at(0) == '#') )
        {
            fileLine += 1;
            continue;
        }

        // check for spawn block
        if( nextLine.at(0) == '$' )
        {
            int beforeCommaIdx = nextLine.find_first_of(',') - 1;

            if( beforeCommaIdx < 2 ) throw LayoutParseError("Invalid exit block definition");

            if( nextLine.at(beforeCommaIdx) == 'R' ) parsedStartDir = BLK_REVERSE;
            else if( nextLine.at(beforeCommaIdx) == 'F' ) parsedStartDir = BLK_FORWARD;
            else throw LayoutParseError("Invalid exit block direction");

            try
            {
                parsedStartBlockId = parseIntStrict(nextLine.substr(1, beforeCommaIdx - 1));
            }
            catch( const std::invalid_argument &e )
            {
                throw LayoutParseError("Invalid exit block id");
            }

            int afterFirstCommaIdx = beforeCommaIdx + 2;
            int beforeNextCommaIdx = nextLine.find_first_of(',', afterFirstCommaIdx) - 1;
            int dispLen = beforeNextCommaIdx - afterFirstCommaIdx + 1;
            if( dispLen >= 2 )
            {
                // display start specified
                if( nextLine.at(beforeNextCommaIdx) == 'R' ) displayStartDir = BLK_REVERSE;
                else if( nextLine.at(beforeNextCommaIdx) == 'F' ) displayStartDir = BLK_FORWARD;
                else throw LayoutParseError("Invalid display start direction");

                try
                {
                    displayStartBlk = parseIntStrict(nextLine.substr(afterFirstCommaIdx, dispLen - 1));
                }
                catch( const std::invalid_argument &e )
                {
                    throw LayoutParseError("Invalid display start id");
                }
            }

            fileLine += 1;
            continue;
        }

        state = LL_SECTION;
        auto iter = nextLine.begin();

        while( iter != nextLine.end() ) {
            // while we still have tokens to read
            char nextChar = *iter;

            if( nextChar == ',' ) {
                // delimiter read, advance to next state
                std::string bufStr = buf.str();

                try {
                    switch( state ) {
                        case LL_SECTION:
                            sectionName = bufStr;
                            break;

                        case LL_ID:
                            blockNum = parseIntStrict(bufStr);
                            break;

                        case LL_LEN:
                            length = parseFloatStrict(bufStr);
                            break;

                        case LL_GRADE:
                            grade = parseFloatStrict(bufStr) / 100.0f; // convert % to grade
                            break;

                        case LL_SPEED:
                            speedLimit = parseFloatStrict(bufStr);
                            break;

                        case LL_ONEWAY:
                            if( (bufStr.length() == 0) || !bufStr.compare("no") ) oneway = BLK_NODIR;
                            else if( !bufStr.compare("fwd") ) oneway = BLK_FORWARD;
                            else if( !bufStr.compare("rev") ) oneway = BLK_REVERSE;
                            else
                            {
                                buf.str(std::string());
                                buf.clear();
                                buf << "Invalid oneway restriction \"" << bufStr << "\" on line " << fileLine;
                                throw LayoutParseError(buf.str());
                            }
                            break;

                        case LL_TAGS:
                            if( bufStr.length() == 0 )
                            {
                                isTunnel = false;
                                hasCrossing = false;
                            }
                            else
                            {
                                int flags = parseIntStrict(bufStr);
                                isTunnel = flags & TUNNEL_FLAG;
                                hasCrossing = flags & CROSSING_FLAG;
                            }
                            break;

                        case LL_PREV_BLK:
                            if( bufStr.length() == 0 ) blkRev = -1;
                            else blkRev = parseIntStrict(bufStr);
                            break;

                        case LL_NEXT_BLK:
                            if( bufStr.length() == 0 ) blkFwd = -1;
                            else blkFwd = parseIntStrict(bufStr);
                            break;

                        case LL_BRANCH_A:
                            if( bufStr.length() == 0 ) branchRev = -1;
                            else branchRev = parseIntStrict(bufStr);
                            break;

                        case LL_BRANCH_B:
                            if( bufStr.length() == 0 ) branchFwd = -1;
                            else branchFwd = parseIntStrict(bufStr);
                            break;

                        case LL_STATION:
                            buf.str(std::string());
                            buf.clear();
                            buf << "Too many fields on line " << fileLine;
                            throw LayoutParseError(buf.str());
                    }
                }
                catch( const std::invalid_argument &e ) {
                    buf.str(std::string());
                    buf.clear();
                    buf << "Error parsing " << stateNames[state] << " (col " << (state + 1) << ") on line " << fileLine;
                    buf << ": " << e.what();
                    layoutFile.close();
                    throw LayoutParseError(buf.str());
                }
                catch( const std::out_of_range &e ) {
                    buf.str(std::string());
                    buf.clear();
                    buf << "Error parsing field " << stateNames[state] << " on line " << fileLine;
                    buf << ": " << e.what();
                    layoutFile.close();
                    throw LayoutParseError(buf.str());
                }
                catch( const LayoutParseError &e )
                {
                    layoutFile.close();
                    throw e;
                }

                state = static_cast<ParseState>(state + 1);
                buf.str(std::string());
                buf.clear();
            }
            else {
                // Non-delimiter char, append to buf
                buf.put(nextChar);
            }

            // advance to next char of line
            iter++;
        }

        if( state == LL_STATION ) {
            station = buf.str();
            buf.str(std::string());
            buf.clear();
        }
        else {
            buf.str(std::string());
            buf.clear();
            buf << "Too few fields on line " << fileLine;
            layoutFile.close();
            throw LayoutParseError(buf.str());
        }

        // eol reached w/ valid data, process what we read
        Block *newBlock = new Block(blockNum, sectionName, length, grade, speedLimit, oneway, isTunnel, hasCrossing);
        blocks.insert(std::pair<int, Block*>(blockNum, newBlock));


        // save any links and branches to be formed once all blocks are loaded
        LinkInfo b(newBlock, blkRev, blkFwd, branchRev, branchFwd);

        if( b.nonNull() )
        {
            voidLinks.push_back(b);
        }

        // check for station
        if( !station.empty() ) {
            size_t colonIdx = station.find(':');
            PlatformSide side = PS_BOTH;
            if( colonIdx != std::string::npos )
            {
                // found colon
                char sideC = station.at(colonIdx + 1);
                if( sideC == 'L' ) side = PS_LEFT;
                else if( sideC == 'R' ) side = PS_RIGHT;
                else
                {
                    buf.str(std::string());
                    buf.clear();
                    buf << "Invalid platform side on line " << fileLine;
                    throw LayoutParseError(buf.str());
                }
                station = station.substr(0, colonIdx);
            }

            // check for existing station
            for( Station *s : stations )
            {
                if( !station.compare(s->name) )
                {
                    newBlock->platform.station = s;
                    newBlock->platform.side = side;
                    s->attachedBlocks.push_back(newBlock);
                }
            }

            // create new if we didn't find
            if( !newBlock->platform.exists() )
            {
                Station *newStation = new Station(station);
                newBlock->platform.station = newStation;
                newBlock->platform.side = side;
                newStation->attachedBlocks.push_back(newBlock);
                stations.push_back(newStation);
            }
        }

        // proceed to next line
        fileLine += 1;
    }
    // end while

    // eof
    layoutFile.close();

    // find spawn block
    if( parsedStartBlockId <= 0 ) parsedStartBlockId = 1;

    spawnBlock = getBlock(parsedStartBlockId);
    spawnDir = parsedStartDir;
    if( !spawnBlock ) throw LayoutParseError("No valid initial block specified");

    Block *yard = new Block(0, "Yard", 50, 0, 100);
    blocks.insert(std::pair<int, Block*>(0, yard));

    LinkInfo yardExit(yard, -1, parsedStartBlockId, -1, -1);
    voidLinks.push_back(yardExit);

    // loop thru uninitialized switches and connect those suckers
    for( LinkInfo &links : voidLinks )
    {
        if( links.prevStraight >= 0 )
        {
            Block *prevBlock = getBlock(links.prevStraight);
            if( !prevBlock )
            {
                std::stringstream msg = std::stringstream("Invalid previous block ");
                msg << links.nextDiverge << " on block " << links.srcBlock->id;
                throw std::invalid_argument(msg.str());
            }

            // check for tunnel transition (reverse)
            if( prevBlock->underground && !links.srcBlock->underground )
            {
                links.srcBlock->forwardBeacon.applyTunnelData(false); // exiting forward
                links.srcBlock->reverseBeacon.applyTunnelData(true); // entering reverse
            }

            // check for switch in reverse dir
            if( links.prevDiverge >= 0 )
            {
                Block *divergeBlock = getBlock(links.prevDiverge);
                if( !divergeBlock )
                {
                    std::stringstream msg = std::stringstream("Invalid reverse switch target ");
                    msg << links.nextDiverge << " on block " << links.srcBlock->id;
                    throw std::invalid_argument(msg.str());
                }

                Switch *rearSwitch = new Switch(links.srcBlock, BLK_REVERSE, prevBlock, divergeBlock);
                switches.insert({links.srcBlock->id, rearSwitch});

                links.srcBlock->setLink(BLK_REVERSE, rearSwitch);
            }
            else
            {
                // there is no branch, only straight
                links.srcBlock->setLink(BLK_REVERSE, prevBlock);
            }
        }

        if( links.nextStraight >= 0 )
        {
            Block *nextBlock = getBlock(links.nextStraight);
            if( !nextBlock )
            {
                std::stringstream msg = std::stringstream("Invalid next block ");
                msg << links.nextDiverge << " on block " << links.srcBlock->id;
                throw std::invalid_argument(msg.str());
            }

            // check for tunnel transition (forward)
            if( nextBlock->underground && !links.srcBlock->underground )
            {
                links.srcBlock->forwardBeacon.applyTunnelData(true); // entering forward
                links.srcBlock->reverseBeacon.applyTunnelData(false); // exiting in reverse
            }

            // check for switch in forward dir
            if( links.nextDiverge >= 0 )
            {
                Block *divergeBlock = getBlock(links.nextDiverge);
                if( !divergeBlock )
                {
                    std::stringstream msg = std::stringstream("Invalid forward switch target ");
                    msg << links.nextDiverge << " on block " << links.srcBlock->id;
                    throw std::invalid_argument(msg.str());
                }

                Switch *fwdSwitch = new Switch(links.srcBlock, BLK_FORWARD, nextBlock, divergeBlock);
                switches.insert({links.srcBlock->id, fwdSwitch});

                links.srcBlock->setLink(BLK_FORWARD, fwdSwitch);
            }
            else
            {
                // no branch only straight
                links.srcBlock->setLink(BLK_FORWARD, nextBlock);
            }
        }
    }
    
    // Now that the blocks are linked, let's find them stations
    for( auto& kvp : blocks )
    {
        Block *curBlock = kvp.second;

        // check for station on current block
        if( curBlock->platform.exists() )
        {
            PlatformData platform = curBlock->getPlatformInDir(BLK_FORWARD);
            Station *station = platform.station;
            curBlock->forwardBeacon.applyStationData(station->name, platform.side);

            platform = curBlock->getPlatformInDir(BLK_REVERSE);
            curBlock->reverseBeacon.applyStationData(station->name, platform.side);
        }

        // look backwards
        NextBlockData neighbor = curBlock->getNextBlock(BLK_REVERSE);
        if( neighbor.exists() )
        {
            // neighbor exists
            // check for platform in neighber
            PlatformData plat = neighbor.block->getPlatformInDir(neighbor.entryDir);
            if( plat.exists() )
            {
                // platform in adjacent block
                curBlock->reverseBeacon.applyStationData(plat.station->name, plat.side, 1);
            }

            NextBlockData farNeighbor = neighbor.block->getNextBlock(neighbor.entryDir);
            if( farNeighbor.exists() )
            {
                // distant neighbor exists, check for station
                plat = farNeighbor.block->getPlatformInDir(farNeighbor.entryDir);
                if( plat.exists() )
                {
                    curBlock->reverseBeacon.applyStationData(plat.station->name, plat.side, 2);
                }
            }
        }

        // look forwards
        neighbor = curBlock->getNextBlock(BLK_FORWARD);
        if( neighbor.exists() )
        {
            // neighbor exists
            // check for platform in neighber
            PlatformData plat = neighbor.block->getPlatformInDir(neighbor.entryDir);
            if( plat.exists() )
            {
                // platform in adjacent block
                curBlock->forwardBeacon.applyStationData(plat.station->name, plat.side, 1);
            }

            NextBlockData farNeighbor = neighbor.block->getNextBlock(neighbor.entryDir);
            if( farNeighbor.exists() )
            {
                // distant neighbor exists, check for station
                plat = farNeighbor.block->getPlatformInDir(farNeighbor.entryDir);
                if( plat.exists() )
                {
                    curBlock->forwardBeacon.applyStationData(plat.station->name, plat.side, 2);
                }
            }
        }
    }
}

Block *Route::getBlock( int blockId ) {
    Block *requested;

    try {
        requested = blocks.at(blockId);
    }
    catch(const std::out_of_range &e) {
        requested = nullptr;
    }

    return requested;
}

Switch *Route::getSwitch( int fromBlockId ) {
    Switch *requested;

    try
    {
        requested = switches.at(fromBlockId);
    }
    catch(const std::out_of_range &e)
    {
        requested = nullptr;
    }

    return requested;
}

Station *Route::getStationByName( std::string stationName ) {
    for( const auto &station : stations ) {
        if( !stationName.compare(station->name) ) {
            return station;
        }
    }
    return nullptr;
}


//-----------------------------------------------------------------------
// Block Members
Block::Block( int id, std::string section, float length, float grade, float speedLimit, BlockDir oneWay, bool tunnel, bool cross ) :
    id(id), section(section), length(length), grade(grade), speedLimit(speedLimit), oneWay(oneWay),
    platform(), underground(tunnel), crossing(cross),
    reverseLink(nullptr), forwardLink(nullptr) {}

Block *Block::getTarget()
{
    return this;
}

bool Block::hasTarget( Block *tgt )
{
    return (tgt == this);
}

void Block::setLink( BlockDir direction, Linkable *newBlock ) {
    if( direction == BLK_FORWARD ) {
        forwardLink = newBlock;
    }
    else {
        reverseLink = newBlock;
    }
}

Linkable *Block::getLink( BlockDir direction )
{
    return (direction == BLK_FORWARD) ? forwardLink : reverseLink;
}

NextBlockData Block::getNextBlock( BlockDir direction )
{
    NextBlockData data {nullptr, BLK_NODIR};

    if( direction == BLK_FORWARD )
    {
        if( forwardLink )
        {
            data.block = forwardLink->getTarget();
            if( data.block->reverseLink && data.block->reverseLink->hasTarget(this) )
            {
                // next block is same direction, we're searching forward
                data.entryDir = BLK_FORWARD;
            }
            else data.entryDir = BLK_REVERSE;
        }
    }
    else
    {
        // direction == BLK_REVERSE
        if( reverseLink )
        {
            data.block = reverseLink->getTarget();
            if( data.block->forwardLink && data.block->forwardLink->hasTarget(this) )
            {
                // prev block is same direction, we're searching in reverse
                data.entryDir = BLK_REVERSE;
            }
            else data.entryDir = BLK_FORWARD;
        }
    }

    return data;
}

BlockDir Block::getEntryDir( Block *neighbor )
{
    if( neighbor->reverseLink && neighbor->reverseLink->hasTarget(this) ) return BLK_FORWARD;
    if( neighbor->forwardLink && neighbor->forwardLink->hasTarget(this) ) return BLK_REVERSE;
    return BLK_NODIR;
}

bool Block::canTravelInDir( BlockDir direction )
{
    if( oneWay == BLK_NODIR ) return true;
    else return (direction == oneWay);
}

PlatformData Block::getPlatformInDir( BlockDir dir )
{
    if( dir == BLK_REVERSE )
    {
        PlatformData ret = platform;
        ret.side = oppositeSide(platform.side);
        return ret;
    }
    else return platform;
}

BeaconData Block::getBeaconInDir( BlockDir dir )
{
    if( dir == BLK_REVERSE ) return reverseBeacon;
    else return forwardBeacon;
}


//-----------------------------------------------------------------------
// Switch Members
Switch::Switch( Block *from, BlockDir fromDir, Block *straight, Block *diverge ) :
    fromBlock(from), fromBlockDir(fromDir),
    straightBlock(straight), divergeBlock(diverge), direction(SW_STRAIGHT) {}

void Switch::setDirection( SwitchState newState ) {
    direction = newState;
}

Block *Switch::getTarget()
{
    if( direction == SW_DIVERGING ) return divergeBlock;
    else return straightBlock;
}

bool Switch::hasTarget( Block *tgt )
{
    return (tgt == straightBlock) || (tgt == divergeBlock);
}


//-----------------------------------------------------------------------
// Station Members
Station::Station( std::string name ) :
    name(name) {}

