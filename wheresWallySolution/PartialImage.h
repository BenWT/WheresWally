#ifndef partialimage_h
#define partialimage_h

#include "Image.h"

class PartialImage : public Image {
public:
	// Variables
	float searchScore;
	
	// Methods
	void addRow(int* row) {
		double* m = new double[this->width * (this->height + 1)];

		for (int y = 0; y < height + 1; y++) {
			for (int x = 0; x < width; x++) {
				if (y == height) {
					m[x + (y * width)] = row[x];
				}
				else {
					m[x + (y * width)] = matrix[x + (y * width)];
				}
			}
		}

		matrix = m;
		height++;
		count = width * height;
		length = count - 1;
	}

	// Inherit Constructors
	using Image::Image;
};

#endif