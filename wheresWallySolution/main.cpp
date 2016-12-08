#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstddef>

#include "Globals.h"
#include "Matrix.h"
#include "Image.h"
#include "FullImage.h"
#include "PartialImage.h"
#include "SearchImage.h"

using namespace std;

string GetPathFromFullPath(const string&);
string GetfilenameFromFullPath(const string&);
bool ReadImage(string, int , int, double*&);
bool WriteImage(string, PartialImage*);
PartialImage* FindWally(Image*, Image*);
double CompareImages(Image*, Image*, int, int);

int main(int argc, char* argv[])
{
	// Get Base Path
	string basePath = argv[0];
	basePath = GetPathFromFullPath(basePath);

	int numberOfMatches = 1;
	double* fullData = new double[FULL_LENGTH];
	double* subData = new double[SEARCH_LENGTH];

	// Load Image Data
	bool readFull = ReadImage(basePath + "\\images\\Cluttered_scene.txt", FULL_WIDTH, FULL_HEIGHT, fullData);
	bool readSub = ReadImage(basePath + "\\images\\Wally_grey.txt", SEARCH_WIDTH, SEARCH_HEIGHT, subData);

	if (readFull && readSub) {
		// Create Image Objects
		Image* full = new Image(FULL_WIDTH, FULL_HEIGHT, fullData);
		Image* search = new Image(SEARCH_WIDTH, SEARCH_HEIGHT, subData);

		// Solve
		PartialImage* result = FindWally(full, search);
		cout << result->width << " " << result->height << endl;

		// Output to file
		WriteImage(basePath + "\\images\\output.pgm", result);

		delete full;
		delete search;
		delete result;
	} else {
		cout << "Images could not be loaded correctly." << endl;
	}

	system("pause");

	/* delete fullData;
	delete subData; */

	return 0;
}

string GetPathFromFullPath(const string& str) {
	size_t found = str.find_last_of("/\\");
	return str.substr(0, found);
}
string GetfilenameFromFullPath(const string& str) {
	size_t found = str.find_last_of("/\\");
	return str.substr(found + 1);
}

bool ReadImage(string filename, int width, int height, double* &data)
{
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

bool WriteImage(string filename, PartialImage* image)
{
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

PartialImage* FindWally(Image* full, Image* sub)
{
	SearchImage* match = new SearchImage();

	cout << "full: " << full->width << " " << full->height << endl;
	cout << "sub: " << sub->width << " " << sub->height << endl;

	for (int x = 0; x < full->width - sub->width; x++) {
		for (int y = 0; y < full->height - sub->height; y++) {
			double comparisonValue = CompareImages(full, sub, x, y);

			if (comparisonValue < match->difference) {
				match->x = x;
				match->y = y;
				match->difference = comparisonValue;
			}
		}
	}

	cout << match->x << endl;
	cout << match->y << endl;
	
	PartialImage* result = new PartialImage(full, sub->width, sub->height, match->x, match->y);

	return result;
}

double CompareImages(Image* full, Image* sub, int offX, int offY) {
	double variance = 0;

	for (int x = 0; x < sub->width; x++) {
		for (int y = 0; y < sub->height; y++) {
			int fullValue = full->getValue(x + offX, y + offY);
			int searchValue = sub->getValue(x, y);

			if (searchValue < 255) { // white background on search image
				variance += (fullValue - searchValue) * (fullValue - searchValue);
			}
		}
	}

	return variance;
}