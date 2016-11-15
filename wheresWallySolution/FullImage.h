#ifndef fullimage_h
#define fullimage_h

#include "Image.h"

class FullImage : protected Image {
public:
	// Constructors
	FullImage() {
		std::cout << "Initialised Empty Image." << std::endl;
	}
	FullImage(int width, int height) {
		this->width = width;
		this->height = height;

		initialiseMatrix(this->width, this->height);
		fill(0);
	}
};

#endif