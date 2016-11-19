#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include "Image.h"
#include "FullImage.h"
#include "PartialImage.h"
#include "SearchImage.h"

#define FULL_WIDTH 1024
#define FULL_HEIGHT 768
#define FULL_LENGTH FULL_WIDTH * FULL_HEIGHT
#define SEARCH_WIDTH 36
#define SEARCH_HEIGHT 49
#define SEARCH_LENGTH SEARCH_WIDTH * SEARCH_HEIGHT

bool ReadImage(char*, int , int, double*&);
PartialImage* FindWally(FullImage*, SearchImage*);
bool WriteImage(char*, PartialImage*);

int main()
{
	// Load Image Data
	double* fullData = new double[FULL_LENGTH];
	double* searchData = new double[SEARCH_LENGTH];
	bool readFull = ReadImage("Cluttered_scene.txt", FULL_WIDTH, FULL_HEIGHT, fullData);
	bool readSearch = ReadImage("Wally_grey.txt", SEARCH_WIDTH, SEARCH_HEIGHT, searchData);

	if (!readFull || !readSearch) {
		std::cout << "Images could not be loaded correctly." << std::endl;
		return 1;
	}

	// Create images
	FullImage* full = new FullImage(FULL_WIDTH, FULL_HEIGHT, fullData);
	SearchImage* search = new SearchImage(SEARCH_WIDTH, SEARCH_HEIGHT, searchData);

	// Solve
	PartialImage* result = FindWally(full, search);

	// Output to file
	WriteImage("Output.pgm", result);

	delete [] full;
	delete [] search;
	delete [] result;

	return 0;
}

bool ReadImage(char *fileName, int width, int height, double* &data)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "Opened the requested file." << std::endl;

		for (int i = 0; i < width * height; i++) {
			file >> *(data + i);
		}

		file.close();

		return true;
	}
	else {
		std::cout << "Failed to open the requested file." << std::endl;
		return false;
	}
}

PartialImage* FindWally(FullImage* full, SearchImage* search)
{
	PartialImage* result = new PartialImage(search->width, search->height, search->getMatrix());
	std::cout << "Unimplemented Search Function." << std::endl;
	return result;
}

bool WriteImage(char * fileName, PartialImage* image)
{
	unsigned char *out = new unsigned char[image->width * image->height];
	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);

	if (file.is_open()) {
		for (int i = 0; i < image->width * image->height; i++) {
			out[i] = (unsigned char)image->getValue(i);
		}

		file << "P5" << std::endl;
		file << image->width << " " << image->height << std::endl;
		file << 255 << std::endl;
		file.write(reinterpret_cast<char *>(out), (image->width * image->height) * sizeof(unsigned char));

		std::cout << "Wrote contents to file" << std::endl;
		return true;
	}
	else {
		std::cout << "Failed to create the requested file." << std::endl;
		return false;
	}
}