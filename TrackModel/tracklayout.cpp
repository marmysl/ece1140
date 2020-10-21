#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "tracklayout.hpp"

#include <QFileInfo>

using namespace TrackModel;

Block *TrackModel::yard = new Block(0, "Yard", 1, 0, 10000);

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
Route::Route( std::string name ) : name(name) {}

static int parseIntStrict( std::string str ) {
    size_t lenParsed;
    int result = std::stoi(str, &lenParsed);

    if( lenParsed != str.length() ) throw std::invalid_argument(str + " is not a valid integer value");
    return result;
}

static float parseFloatStrict( std::string str ) {
    size_t lenParsed;
    float result = std::stof(str, &lenParsed);

    if( lenParsed != str.length() ) throw std::invalid_argument(str + " is not a valid floating point value");
    return result;
}

void Route::loadLayout( std::string fileName ) {
    std::ifstream layoutFile;

    QFileInfo lfInfo(QString::fromStdString(fileName));
    layoutFile.open(lfInfo.absoluteFilePath().toStdString(), std::ios::in);

    if( !layoutFile.is_open() ) throw std::invalid_argument ("Unable to open layout file");

    std::string nextLine;
    std::stringstream buf = std::stringstream ();

    // oh boy a parser
    enum ParseState {
        LL_NAME, LL_SECTION, LL_ID, LL_LEN, LL_GRADE, LL_SPEED, LL_PREV_BLK, LL_NEXT_BLK, LL_BRANCH_A, LL_BRANCH_B, LL_STATION
    };

    const char *stateNames[] {
        "Name", "Section", "BlockId", "Length", "Grade", "Speed Limit", "Branch Rev", "Branch Fwd", "Station"
    };

    // getline() <---------------------------------------------------------------
    //   |                                                                       |
    //   v                                                                       |
    // name -> section -> id -> len -> grade -> speed -> branchA -> branchB -> station

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

    std::string lineName;
    std::string sectionName;
    int blockNum;
    float length;
    float grade;
    float speedLimit;

    int blkRev, blkFwd;
    int branchRev;
    int branchFwd;
    std::string station;

    // for each line of the config file
    while( getline(layoutFile, nextLine) ) {
        state = LL_NAME;
        auto iter = nextLine.begin();

        while( iter != nextLine.end() ) {
            // while we still have tokens to read
            char nextChar = *iter;

            if( nextChar == ',' ) {
                // delimiter read, advance to next state
                std::string bufStr = buf.str();

                try {
                    switch( state ) {
                        case LL_NAME:
                            lineName = bufStr;
                            break;

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
                            grade = parseFloatStrict(bufStr);
                            break;

                        case LL_SPEED:
                            speedLimit = parseFloatStrict(bufStr);
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
                            layoutFile.close();
                            throw LayoutParseError(buf.str());
                    }
                }
                catch( const std::invalid_argument &e ) {
                    buf.str(std::string());
                    buf.clear();
                    buf << "Error parsing field " << stateNames[state] << " on line " << fileLine;
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
        Block *newBlock = new Block(blockNum, sectionName, length, grade, speedLimit);
        blocks.insert(std::pair<int, Block*>(blockNum, newBlock));


        // save any links and branches to be formed once all blocks are loaded
        LinkInfo b(newBlock, blkRev, blkFwd, branchRev, branchFwd);

        if( b.nonNull() )
        {
            voidLinks.push_back(b);
        }

        // check for station
        if( !station.empty() ) {
            Station *newStation = new Station(station);
            newBlock->station = newStation;
            stations.push_back(newStation);
        }

        // proceed to next line
        fileLine += 1;
    }
    // end while

    // eof
    layoutFile.close();

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
    
}

Block *Route::getBlock( int blockId ) {
    Block *requested;

    if( blockId == 0 ) return yard;

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
Block::Block( int id, std::string section, float length, float grade, float speedLimit, BlockDir oneWay ) :
    id(id), section(section), length(length), grade(grade), speedLimit(speedLimit), oneWay(oneWay),
    station(nullptr), prevBlock(nullptr), nextBlock(nullptr) {}

Block *Block::getTarget()
{
    return this;
}

void Block::setLink( BlockDir direction, Linkable *newBlock ) {
    if( direction == BLK_FORWARD ) {
        nextBlock = newBlock;
    }
    else {
        prevBlock = newBlock;
    }
}

Block *Block::getLink( BlockDir direction )
{
    if( direction == BLK_FORWARD )
    {
        return nextBlock ? nextBlock->getTarget() : nullptr;
    }
    else
    {
        return prevBlock ? prevBlock->getTarget() : nullptr;
    }
}


//-----------------------------------------------------------------------
// Switch Members
Switch::Switch( Block *from, BlockDir fromDir, Block *straight, Block *diverge ) :
    fromBlock(from), fromBlockDir(fromDir),
    straightBlock(straight), divergeBlock(diverge), direction(SW_STRAIGHT) {}

void Switch::setDirection( SwitchState newState ) {
    if( newState == SW_DIVERGING ) {
        fromBlock->setLink(fromBlockDir, divergeBlock);
    }
    else {
        fromBlock->setLink(fromBlockDir, straightBlock);
    }

    direction = newState;
}

Block *Switch::getTarget()
{
    if( direction == SW_DIVERGING ) return divergeBlock;
    else return straightBlock;
}


//-----------------------------------------------------------------------
// Station Members
Station::Station( std::string name ) :
    name(name) {}

