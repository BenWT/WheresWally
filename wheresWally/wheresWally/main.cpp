//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include "Globals.h"
#include "Image.h"
#include "LargeImage.h"
#include "MatchImage.h"

using namespace std;
bool ReadImage(string, int, int, double*&);
bool WriteImage(string, MatchImage*);
MatchImage* DoSearch(LargeImage*, Image*);
double CompareImages(LargeImage*, Image*, int, int);

string GetPathFromFullPath(const string& str) {
	size_t found = str.find_last_of("/\\");
	if (found == numeric_limits<size_t>::max()) return "";
	else return str.substr(0, found) + "\\";
}
string GetfilenameFromFullPath(const string& str) {
	size_t found = str.find_last_of("/\\");
	if (found == numeric_limits<size_t>::max()) return str;
	else return str.substr(found + 1);
}

int main(int argc, char *argv[])
{
	// Get Base Path
	string basePath = argv[0];
	basePath = GetPathFromFullPath(basePath);

	// Load Image Data
	double* largeData = new double[LARGE_LENGTH];
	double* searchData = new double[SEARCH_LENGTH];
	bool readLarge = ReadImage(basePath + "images\\Cluttered_scene.txt", LARGE_WIDTH, LARGE_HEIGHT, largeData);
	bool readSub = ReadImage(basePath + "images\\Wally_grey.txt", SEARCH_WIDTH, SEARCH_HEIGHT, searchData);

	if (readLarge && readSub) {
		// Instantiate Image Objects
		LargeImage* largeImage = new LargeImage(LARGE_WIDTH, LARGE_HEIGHT, largeData);
		Image* searchImage = new Image(SEARCH_WIDTH, SEARCH_HEIGHT, searchData);
		MatchImage* result = DoSearch(largeImage, searchImage);

		WriteImage(basePath + "images\\output.pgm", result);

		delete largeImage;
		delete searchImage;
	}
	else {
		cout << "Images could not be loaded correctly." << endl;
	}

	delete[] largeData;
	delete[] searchData;

	return 0;
}

bool ReadImage(string filename, int width, int height, double* &data) {
	ifstream file(filename.c_str());

	if (file.is_open()) {
		cout << "Successfully opened " << GetfilenameFromFullPath(filename) << endl;

		for (int i = 0; i < width * height; i++) {
			file >> *(data + i);
		}

		file.close();

		return true;
	}
	else {
		cout << "Failed to open the requested file." << endl;
		return false;
	}
}

bool WriteImage(string filename, MatchImage* image) {
	unsigned char *out = new unsigned char[image->width * image->height];
	ofstream file;
	file.open(filename.c_str(), ios::out | ios::binary | ios::trunc);

	if (file.is_open()) {
		for (int i = 0; i < image->width * image->height; i++) {
			out[i] = (unsigned char)image->getValue(i);
		}

		file << "P5" << endl;
		file << image->width << " " << image->height << endl;
		file << 255 << endl;
		file.write(reinterpret_cast<char *>(out), (image->width * image->height) * sizeof(unsigned char));

		cout << "Wrote contents to " << GetfilenameFromFullPath(filename) << endl;
		return true;
	}
	else {
		cout << "Failed to create the requested file." << endl;
		return false;
	}
}

MatchImage* DoSearch(LargeImage* largeImage, Image* search) {
	cout << "Searching..." << endl;

	int bestX = 0, bestY = 0;
	double bestComparision = std::numeric_limits<double>::max();

	for (int x = 0; x < largeImage->width - search->width; x++) {
		for (int y = 0; y < largeImage->height - search->height; y++) {

			double comparision = CompareImages(largeImage, search, x, y);

			if (comparision < bestComparision) {
				bestX = x;
				bestY = y;
				bestComparision = comparision;
			}
		}
	}

	cout << "Done Searching." << endl;
	MatchImage* result = largeImage->CreatePartial(search->width, search->height, bestX, bestY);
	return result;
}

double CompareImages(LargeImage* largeImage, Image* search, int offsetX, int offsetY) {
	double variance = 0.0;

	for (int x = 0; x < search->width; x++) {
		for (int y = 0; y< search->height; y++) {
			double fullValue = largeImage->getValue(x + offsetX, y + offsetY);
			double matchValue = search->getValue(x, y);

			if (matchValue < 255) {
				variance += (fullValue - matchValue) * (fullValue - matchValue);
			}
		}
	}

	return variance;
}
