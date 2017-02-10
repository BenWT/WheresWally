//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#include "MatchData.h"

MatchData::MatchData() {
	this->x = 0;
	this->y = 0;
	this->comparison = std::numeric_limits<double>::max();
}
MatchData::MatchData(int x, int y, double comparison) {
	this->x = x;
	this->y = y;
	this->comparison = comparison;
}