#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <cstddef>

#include "Globals.h"
#include "Image.h"
#include "FullImage.h"
#include "PartialImage.h"
#include "SearchImage.h"

using namespace std;

string GetPathFromFullPath(const string&);
string GetfilenameFromFullPath(const string&);
bool ReadImage(string, int , int, double*&);
bool WriteImage(string, PartialImage*);
PartialImage* FindWally(FullImage*, SearchImage*);
double CompareImages(FullImage*, SearchImage*, int, int);

int main(int argc, char* argv[])
{
	// Get Base Path
	string basePath = argv[0];
	basePath = GetPathFromFullPath(basePath);

	int numberOfMatches = 1;
	double* fullData = new double[FULL_LENGTH];
	double* searchData = new double[SEARCH_LENGTH];

	// Load Image Data
	bool readFull = ReadImage(basePath + "\\images\\Cluttered_scene.txt", FULL_WIDTH, FULL_HEIGHT, fullData);
	bool readSearch = ReadImage(basePath + "\\images\\Wally_grey.txt", SEARCH_WIDTH, SEARCH_HEIGHT, searchData);

	if (readFull && readSearch) {
		cout << "Please enter the number of matches you would like to save: ";
		cin >> numberOfMatches;
		if (numberOfMatches < 1) numberOfMatches = 1;

		// Create Image Objects
		FullImage* full = new FullImage(FULL_WIDTH, FULL_HEIGHT, fullData);
		SearchImage* search = new SearchImage(SEARCH_WIDTH, SEARCH_HEIGHT, searchData);

		// Solve
		PartialImage* result = FindWally(full, search);

		// Output to file
		WriteImage(basePath + "\\images\\output.pgm", result);

		delete full;
		delete search;
		delete result;
	} else {
		cout << "Images could not be loaded correctly." << endl;
	}

	system("pause");

	delete fullData;
	delete searchData;

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

PartialImage* FindWally(FullImage* full, SearchImage* search)
{
	//PartialImage* result = new PartialImage(search->width, search->height);

	int bestX = 0; int bestY = 0; double lowestDiff = numeric_limits<double>::max();

	for (int x = 0; x < full->width - search->width; x++) {
		for (int y = 0; y < full->height - search->height; y++) {
			double comparisonValue = CompareImages(full, search, x, y);

			if (comparisonValue < lowestDiff) {
				bestX = x;
				bestY = y;
				lowestDiff = comparisonValue;
			}
		}
	}
	cout << bestX << endl;
	cout << bestY << endl;

	PartialImage* result = new PartialImage(full, search->width, search->height, bestX, bestY);
	return result;

	// http://stackoverflow.com/questions/12598818/finding-a-picture-in-a-picture-with-java
}

double CompareImages(FullImage* full, SearchImage* search, int offX, int offY) {
	double variance = 0;

	for (int x = 0; x < search->width; x++) {
		for (int y = 0; y < search->height; y++) {
			int fullValue = full->getValue(x + offX, y + offY);
			int searchValue = search->getValue(x, y);

			if (searchValue < 255) { // white background on search image
				variance += (fullValue - searchValue) * (fullValue - searchValue);
			}
		}
	}

	return variance;
}
