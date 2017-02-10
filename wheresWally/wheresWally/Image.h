//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#pragma once

class Image
{
public:
	// Variables
	int width, height, count, length;
	
	// Methods
	double* getMatrix();
	void setMatrix(double* values);
	double getValue(int i);
	double getValue(int x, int y);
	virtual void setValue(int i, double val);
	virtual void setValue(int x, int y, double val);
	void fill(int vall);
	void print();

	// Constructors
	Image();
	Image(int width, int height);
	Image(int width, int height, double* matrix);
	Image(const Image& other);
	~Image();

	// Operator Overloads
	Image& operator+=(const Image& other);
	friend Image operator+(Image left, const Image& right);
	Image& operator-=(const Image& other);
	friend Image operator-(Image left, const Image& right);
	Image& operator*=(const Image& other);
	friend Image operator*(Image left, const Image& right);
	Image* operator=(const Image& other);

protected:
	double* structure;
};

