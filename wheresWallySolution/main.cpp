#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include "Globals.h"
#include "Image.h"
#include "FullImage.h"
#include "PartialImage.h"
#include "SearchImage.h"

bool ReadImage(char*, int , int, double*&);
bool WriteImage(char*, PartialImage*);
PartialImage* FindWally(FullImage*, SearchImage*);

int main()
{
	// Load Image Data
	double* fullData = new double[FULL_LENGTH];
	double* searchData = new double[SEARCH_LENGTH];
	bool readFull = ReadImage("images/Cluttered_scene.txt", FULL_WIDTH, FULL_HEIGHT, fullData);
	bool readSearch = ReadImage("images/Wally_grey.txt", SEARCH_WIDTH, SEARCH_HEIGHT, searchData);

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
	WriteImage("images/output.pgm", result);

	system("pause"); // TODO Remove for release

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

PartialImage* FindWally(FullImage* full, SearchImage* search)
{
	//PartialImage* result = new PartialImage(search->width, search->height, search->getMatrix());

	int bestX = 0; int bestY = 0; double lowestDiff = std::numeric_limits<double>::max();

	/* for (int x = 0; x < full->width - search->width; x++) {
		for (int y = 0; y < full->height - search->height; y++) {
			double comparisonValue = 0;

			if (comparisonValue < lowestDiff) {
				bestX = x;
				bestY = y;
				lowestDiff = comparisonValue;
			}
		}
	} */

	PartialImage* result = new PartialImage(full, search->width, search->height, 0, 0);
	return result;
	// http://stackoverflow.com/questions/12598818/finding-a-picture-in-a-picture-with-java
}