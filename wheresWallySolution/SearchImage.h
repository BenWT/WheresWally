#pragma once

#include "Image.h"

class SearchImage {
public:
	int x;
	int y;
	double difference;

	SearchImage() {
		this->x = 0;
		this->y = 0;
		this->difference = std::numeric_limits<double>::max();
	}
	SearchImage(int x, int y, double d) {
		this->x = x;
		this->y = y;
		this->difference = d;
	}
};