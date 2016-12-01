#pragma once

#include <iostream>
#include "Matrix.h"

class Image {
public:
	// Variables
	int width;
	int height;
	int count;
	int length;

	// Methods
	double boundValue(double val) {
		if (val > 255) {
			return 255.0;
		}
		else if (val < 0) {
			return 0.0;
		}
		else {
			return val;
		}
	}
	double* getMatrix() {
		return matrix->getMatrix();
	}
	double getValue(int i) {
		return matrix->getValue(i);
	}
	double getValue(int x, int y) {
		return matrix->getValue(x + (y * width));
	}
	void setValue(int i, double val) {
		matrix->setValue(i, boundValue(val));
	}
	void setValue(int x, int y, double val) {
		matrix->setValue(x, y, boundValue(val));
	}
	void fill(int val) {
		matrix->fill(val);
	}
	void print() {
		matrix->print();
	}

	// Constructors
	Image() {
		std::cout << "Initialised Empty Image." << std::endl;
	}
	Image(int width, int height) {
		this->width = width;
		this->height = height;
		this->matrix = new Matrix(width, height);

		fill(0);
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

	//Operator Overloads
	// TODO Implement arithmetics
	Image* operator=(const Image& other) {
		this->width = other.width;
		this->height = other.height;
		this->matrix = other.matrix;

		return this;
	}

protected:
	Matrix* matrix;
};

