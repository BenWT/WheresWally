#pragma once

#include "Image.h"

class PartialImage : public Image {
public:
	// Constructors
	PartialImage(FullImage* full, int width, int height, int startX, int startY) {
		this->width = width;
		this->height = height;

		this->matrix = new Matrix(width, height);;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				setValue(x, y, full->getValue(startX + x, startY + y));
			}
		}
	}
};
