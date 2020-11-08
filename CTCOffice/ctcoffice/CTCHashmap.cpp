#include "CTCHashmap.h"
#include "TrackModel/tracklayout.hpp"

CTCHashmap::CTCHashmap()
{

}

void CTCHashmap::resetLayout(){
    ctcmap.clear();

    for(Route *rte : TrackModel::routes){
        CTCRouteStatus *temp;
        temp = new CTCRouteStatus(rte);
        for(auto blk: rte->blocks){
            temp->addBlock(blk.second);
        }
        ctcmap[rte->name] = temp;
    }

}

CTCRouteStatus* CTCHashmap::getRouteStatus(std::string name){
    return ctcmap.at(name);
}

CTCHashmap ctcmap;
