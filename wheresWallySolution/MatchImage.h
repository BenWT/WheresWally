#pragma once

#include "Image.h"
#include "SearchImage.h"

class MatchImage : public Image {
public:
	int offsetX;
	int offsetY;

	// Constructors
	MatchImage(Image* full, int w, int h, int startX, int startY) {
		this->width = w;
		this->height = h;
		this->offsetX = startX;
		this->offsetY = startY;
		this->matrix = new Matrix(width, height);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				double val = full->matrix->getValue(offsetX + x, offsetY + y);
				this->matrix->setValue(x, y, val);
			}
		}
	}
};
