#ifndef CTCHASHMAP_H
#define CTCHASHMAP_H

#include "CTCDispatch.h"
#include "CTCMode.h"
#include "CTCBlockDisplay.h"
#include "CTCBlockStatus.h"

#include <unordered_map>

class CTCHashmap
{
private:
    std::unordered_map <std::string, CTCRouteStatus*> ctcmap;
public:
    CTCHashmap();
    void resetLayout();
    CTCRouteStatus* getRouteStatus(std::string);
};

extern CTCHashmap ctcmap;

#endif // CTCHASHMAP_H
