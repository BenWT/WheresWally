#pragma once

#include <cassert>

class Matrix {
public:
	int width, height, count, length;

	double* getMatrix() {
		return structure;
	}
	void setMatrix(double* values) {
		this->structure = values;
	}
	double getValue(int i) {
		return structure[i];
	}
	double getValue(int x, int y) {
		return structure[x + (y * width)];
	}
	void setValue(int i, double val) {
		structure[i] = val;
	}
	void setValue(int x, int y, double val) {
		structure[x + (y * width)] = val;
	}
	void fill(int val) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				structure[x + (y * width)] = val;
			}
		}
	}
	void print() {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				std::cout << structure[x + (y * width)] << " ";
			}
			std::cout << std::endl;
		}
	}

	Matrix(int width, int height) {
		this->width = width;
		this->height = height;

		count = this->width * this->height;
		length = count - 1;

		structure = new double[count];
	}
	Matrix(int width, int height, double* matrix) {
		this->width = width;
		this->height = height;

		count = this->width * this->height;
		length = count - 1;

		this->structure = matrix;
	}
	~Matrix() {
		delete[] structure;
	}
	Matrix* operator+(const Matrix& other) {
		Matrix* temp = new Matrix(other.width, other.height);

		for (int i = 0; i < other.width * other.height; i++) {
			temp->setValue(i, this->structure[i] + other.structure[i]);
		}

		return temp;
	}
	Matrix* operator-(const Matrix& other) {
		Matrix* temp = new Matrix(other.width, other.height);

		for (int i = 0; i < other.width * other.height; i++) {
			temp->setValue(i, this->structure[i] - other.structure[i]);
		}

		return temp;
	}
	Matrix* operator=(const Matrix& other) {
		delete[] structure;

		this->width = other.width;
		this->height = other.height;
		this->count = other.count;
		this->length = other.length;
		this->structure = other.structure;

		return this;
	}
	Matrix* operator*(const Matrix& other) {
		assert(this->width == other.height);
		int commonValue = this->width;

		Matrix* temp = new Matrix(other.width, this->height);

		for (int x = 0; x < temp->width; x++) {
			for (int y = 0; y < temp->height; y++) {
				int value = 0;

				for (int i = 0; i < commonValue; i++) {
					value += this->structure[i, y] + other.structure[x, i];
				}

				temp->setValue(x, y, value);
			}
		}
	}
protected:
	double* structure;
};