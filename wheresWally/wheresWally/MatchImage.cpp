//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#include <limits>
#include "MatchImage.h"

// Methods
void MatchImage::setValue(int x, int y, double val) {
	this->structure[(x - offsetX) + ((y - offsetY) * width)] = val;
}

// Constructors
MatchImage::MatchImage() {
	this->width = 0;
	this->height = 0;
	this->offsetX = 0;
	this->offsetY = 0;
	this->count = 1;
	this->length = 0;
	this->structure = new double[count];
}
MatchImage::MatchImage(int width, int height, int offsetX, int offsetY) {
	this->width = width;
	this->height = height;
	this->offsetX = offsetX;
	this->offsetY = offsetY;

	this->count = this->width * this->height;
	this->length = count - 1;

	this->structure = new double[count];
}