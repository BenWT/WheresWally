#ifndef partialimage_h
#define partialimage_h

#include "Image.h"

class PartialImage : public Image {
public:
	// Variables
	float searchScore;
	
	// Methods
	void addRow(int* row) {
		int* m = new int[this->width * (this->height + 1)];

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

	// Constructors
	PartialImage() {
		std::cout << "Initialised Empty Image." << std::endl;
	}
	PartialImage(int width, int height) {
		this->width = width;
		this->height = height;

		initialiseMatrix(this->width, this->height);
		fill(0);
	}
};

#endif