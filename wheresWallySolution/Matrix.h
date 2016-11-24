#pragma once

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
	// TODO: Operator overloads
protected:
	double* structure;
};