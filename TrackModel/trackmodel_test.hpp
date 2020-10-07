#pragma once

#include <string>
#include "tracklayout.hpp"

const std::string LAYOUT_FILE = "blue_line.csv";
const std::string ROUTE_NAME = "Blue Line";

TrackModel::Route *initTestLayout();

int trackModelTestMain();