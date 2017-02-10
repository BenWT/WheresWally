//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#pragma once

#include <limits>
#include "Image.h"

class MatchData : public Image
{
public:
	// Variables
	int x = 0, y = 0;
	double comparison = std::numeric_limits<double>::max();

	// Methods
	

	// Constructors
	MatchData();
	MatchData(int, int, double);
};

