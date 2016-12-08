#pragma once

#include <iostream>
#include "Matrix.h"

class Image {
public:
	// Variables
	int width;
	int height;
	Matrix* matrix;

	double boundValue(double val) {
		if (val > 255.0) return 255.0;
		else if (val < 0.0) return 0.0;
		else return val;
	}

	// Constructors
	Image() {}
	Image(int width, int height) {
		this->width = width;
		this->height = height;
		this->matrix = new Matrix(width, height);
		this->matrix->fill(0);
	}
	Image(int width, int height, double* matrix) {
		this->width = width;
		this->height = height;
		this->matrix = new Matrix(width, height, matrix);
	}
	Image(const Image& other) {
		this->width = other.width;
		this->height = other.height;
		this->matrix = other.matrix;
	}

	// Operator Overloads
	// TODO :: Add other operators
	Image* operator=(const Image& other) {
		this->width = other.width;
		this->height = other.height;
		this->matrix = other.matrix;

		return this;
	}
};
