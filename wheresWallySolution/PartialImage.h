#pragma once

#include "Image.h"
#include "SearchImage.h"

class PartialImage : public Image {
public:
	// Constructors
	PartialImage(Image* full, int w, int h, int startX, int startY) {
		this->width = w;
		this->height = h;

		//this->matrix = new Matrix(width, height);
		this->structure = new double[width*height];

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				double val = full->getValue(startX + x, startY + y);
				setValue(x, y, full->getValue(startX + x, startY + y));
			}
		}
	}
};
