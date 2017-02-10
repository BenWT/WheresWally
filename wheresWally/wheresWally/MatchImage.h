//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#pragma once

#include "Image.h"

class MatchImage : public Image
{
public:
	// Variables
	int offsetX, offsetY;

	// Methods
	void setValue(int, int, double);

	// Constructors
	MatchImage();
	MatchImage(int, int, int, int);

	// Inherit Operator Overloads
	using Image::operator+=;
	using Image::operator-=;
	using Image::operator*=;
	using Image::operator=;
};

