#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "tracklayout.hpp"

#include <QFileInfo>

using namespace TrackModel;

Block *TrackModel::yard;

std::vector<Route *> TrackModel::routes = std::vector<Route *>();

Route *TrackModel::getRoute( std::string name ) {
    for( Route *r : routes ) {
        if( !name.compare(r->name) ) {
            return r;
        }
    }

    return NULL;
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
        LL_NAME, LL_SECTION, LL_ID, LL_LEN, LL_GRADE, LL_SPEED, LL_BRANCH_A, LL_BRANCH_B, LL_STATION
    };

    const char *stateNames[] {
        "Name", "Section", "BlockId", "Length", "Grade", "Speed Limit", "Branch Rev", "Branch Fwd", "Station"
    };

    // getline() <---------------------------------------------------------------
    //   |                                                                       |
    //   v                                                                       |
    // name -> section -> id -> len -> grade -> speed -> branchA -> branchB -> station

    struct BranchInfo {
        int destId;
        Block *srcBlock;
        BlockDir srcDir;

        BranchInfo( int dest, Block *src, BlockDir dir ) : destId(dest), srcBlock(src), srcDir(dir) {}
    };

    ParseState state;
    int fileLine = 1;

    std::vector<BranchInfo> voidBranches = std::vector<BranchInfo> ();
    Block *prevBlock = NULL;

    std::string lineName;
    std::string sectionName;
    int blockNum;
    float length;
    float grade;
    float speedLimit;
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

        newBlock->prevBlock = prevBlock;
        if( prevBlock != NULL ) {
            prevBlock->nextBlock = newBlock;
        }

        // check for switch in reverse dir
        if( branchRev >= 0 ) {
            BranchInfo b = BranchInfo(branchRev, newBlock, BLK_REVERSE);
            voidBranches.push_back(b);
        }

        // check for switch in forward dir
        if( branchFwd >= 0 ) {
            BranchInfo b = BranchInfo(branchFwd, newBlock, BLK_FORWARD);
            voidBranches.push_back(b);
        }

        // check for station
        if( !station.empty() ) {
            newBlock->station = new Station(station);
        }

        prevBlock = newBlock;

        // proceed to next line
        fileLine += 1;
    }

    // eof
    layoutFile.close();

    // loop thru uninitialized switches and connect those suckers
    for( BranchInfo &branch : voidBranches ) {
        Block *divergeBlock = getBlock(branch.destId);
        
        if( divergeBlock == NULL ) {
            std::stringstream msg = std::stringstream("Invalid switch target ");
            msg << branch.destId << " on block " << branch.srcBlock->id;
            throw std::invalid_argument(msg.str());
        }
        
        Block *straightBlock;
        if( branch.srcDir == BLK_FORWARD ) {
            straightBlock = branch.srcBlock->nextBlock;
        }
        else {
            straightBlock = branch.srcBlock->prevBlock;
        }

        Switch *newSwitch = new Switch(branch.srcBlock, branch.srcDir, straightBlock, divergeBlock);
        switches.insert(std::pair<int, Switch *>(branch.srcBlock->id, newSwitch));
    }
    
}

Block *Route::getBlock( int blockId ) {
    Block *requested;

    try {
        requested = blocks.at(blockId);
    }
    catch(const std::out_of_range &e) {
        requested = NULL;
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
        requested = NULL;
    }

    return requested;
}

Station *Route::getStationByName( std::string stationName ) {
    for( const auto &station : stations ) {
        if( !stationName.compare(station->name) ) {
            return station;
        }
    }
    return NULL;
}


//-----------------------------------------------------------------------
// Block Members
Block::Block( int id, std::string section, float length, float grade, float speedLimit ) :
    id(id), section(section), length(length), grade(grade), speedLimit(speedLimit),
    nextBlock(NULL), prevBlock(NULL), station(NULL) {}

void Block::setLink( BlockDir direction, Block *newBlock ) {
    if( direction == BLK_FORWARD ) {
        nextBlock = newBlock;
    }
    else {
        prevBlock = newBlock;
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


//-----------------------------------------------------------------------
// Station Members
Station::Station( std::string name ) :
    name(name) {}

int Station::removePassengers( int maxCount ) {
    if( numPassengers < maxCount ) {
        int curCount = numPassengers;
        numPassengers = 0;
        return curCount;
    }
    else {
        numPassengers -= maxCount;
        return maxCount;
    }
}
