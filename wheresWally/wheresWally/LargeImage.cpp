//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#include <iostream>
#include "LargeImage.h"

MatchImage* LargeImage::CreatePartial(int width, int height, int startX, int startY) {
	MatchImage* result = new MatchImage(width, height, startX, startY);

	for (int y = startY; y < startY + height; y++) {
		for (int x = startX; x < startX + width; x++) {
			result->setValue(x, y, this->getValue(x, y));
		}
	}

	return result;
}