//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#pragma once

#include "Image.h"
#include "MatchImage.h"

class LargeImage : public Image
{
public:
	// Methods
	void setValue(int, double);
	void setValue(int, int, double);
	MatchImage* CreatePartial(int, int, int, int);

	// Inherit Constructors
	using Image::Image;

	// Inherit Operator Overloads
	using Image::operator+=;
	using Image::operator-=;
	using Image::operator*=;
	using Image::operator=;
};

