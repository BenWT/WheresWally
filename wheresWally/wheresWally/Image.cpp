//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#include <iostream>
#include <cassert>
#include "Image.h"

// Methods
double* Image::getMatrix() {
	return structure;
}
void Image::setMatrix(double* values) {
	// TODO hard copy
	this->structure = values;
}
double Image::getValue(int i) {
	return structure[i];
}
double Image::getValue(int x, int y) {
	return structure[x + (y * width)];
}
void Image::setValue(int i, double val) {
	structure[i] = val;
}
void Image::setValue(int x, int y, double val) {
	structure[x + (y * width)] = val;
}
void Image::fill(int val) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			structure[x + (y * width)] = val;
		}
	}
}
void Image::print() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			std::cout << structure[x + (y * width)] << " ";
		}
		std::cout << std::endl;
	}
}

// Constructors
Image::Image() {}
Image::Image(int width, int height) {
	this->width = width;
	this->height = height;

	this->count = this->width * this->height;
	this->length = count - 1;

	this->structure = new double[count];
}
Image::Image(int width, int height, double* matrix) {
	this->width = width;
	this->height = height;

	this->count = this->width * this->height;
	this->length = count - 1;

	this->structure = matrix; // TODO Hard copy
} 
Image::Image(const Image& other) {
	delete[] structure;

	this->width = other.width;
	this->height = other.height;
	this->count = other.count;
	this->length = other.length;
	this->structure = other.structure; // TODO Hard copy
}

// Operator Overloads
Image& Image::operator+=(const Image& other) {
	assert(this->width == other.width);
	assert(this->height == other.height);

	Image temp = Image(other.width, other.height);

	for (int i = 0; i < other.width * other.height; i++) {
		temp.setValue(i, this->structure[i] + other.structure[i]);
	}

	return temp;
}
Image operator+(Image left, const Image& right) {
	left += right;
	return left;
}
Image& Image::operator-=(const Image& other) {
	assert(this->width == other.width);
	assert(this->height == other.height);

	Image temp = Image(other.width, other.height);

	for (int i = 0; i < other.width * other.height; i++) {
		temp.setValue(i, this->structure[i] - other.structure[i]);
	}

	return temp;
}
Image operator-(Image left, const Image& right) {
	left -= right;
	return left;
}
Image& Image::operator*=(const Image& other) {
	assert(this->width == other.height);
	int common = this->width;
	double value = 0;

	Image temp = Image(other.width, this->height);

	for (int x = 0; x < temp.width; x++) {
		for (int y = 0; y < temp.height; y++) {
			value = 0;

			for (int i = 0; i < common; i++) {
				value += this->structure[i, y] + other.structure[x, i];
			}

			temp.setValue(x, y, value);
		}
	}

	return temp;
}
Image operator*(Image left, const Image& right) {
	left *= right;
	return left;
}
Image* Image::operator=(const Image& other) {
	delete[] structure;

	this->width = other.width;
	this->height = other.height;
	this->count = other.count;
	this->length = other.length;
	this->structure = other.structure;

	return this;
}
