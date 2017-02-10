//
// Copyright (c) 2016 by Ben Townshend. All Rights Reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <algorithm>
#include "Globals.h"
#include "Image.h"
#include "LargeImage.h"
#include "MatchImage.h"
#include "MatchData.h"

using namespace std;

bool ReadImage(string, int, int, double*&);
bool WriteImage(string, MatchImage*);
void BubbleSort(vector<MatchData*>&);
vector<MatchImage*> DoSearch(LargeImage*, Image*, int);
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
	int matches = 0;
	double* largeData = new double[LARGE_LENGTH];
	double* searchData = new double[SEARCH_LENGTH];
	bool readLarge = ReadImage(basePath + "images\\Cluttered_scene.txt", LARGE_WIDTH, LARGE_HEIGHT, largeData);
	bool readSub = ReadImage(basePath + "images\\Wally_grey.txt", SEARCH_WIDTH, SEARCH_HEIGHT, searchData);

	cout << "Please enter the number of matches you would like to enter:" << endl;
	while (!(cin >> matches) || matches <= 0) // Repeatedly cin until matches is above 0
	{
		cout << "Please enter a valid number: ";

		// Clear Input
		cin.clear();
		cin.ignore(INT_MAX, '\n'); 
	}

	if (readLarge && readSub) {
		// Instantiate Image Objects
		LargeImage* largeImage = new LargeImage(LARGE_WIDTH, LARGE_HEIGHT, largeData);
		Image* searchImage = new Image(SEARCH_WIDTH, SEARCH_HEIGHT, searchData);
		vector<MatchImage*> results = DoSearch(largeImage, searchImage, matches);

		int counter = 1;
		vector<MatchImage*>::iterator it;
		for (it = results.begin(); it < results.end(); it++) {
			WriteImage(basePath + "images\\output" + to_string(counter) + ".pgm", *it);
			counter++;
		}

		for (it = results.begin(); it < results.end(); it++) {
			delete (*it);
		}
		results.clear();
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

void BubbleSort(vector<MatchData*>& matches) {
	bool shouldSort = true, didSwap = false;

	while (shouldSort) {
		for (int i = 0; i < matches.size() - 1; i++) {
			if (matches.at(i)->comparison > matches.at(i + 1)->comparison) {
				MatchData* temp = matches.at(i);
				matches.at(i) = matches.at(i + 1);
				matches.at(i + 1) = temp;
				didSwap = true;
			}
		}

		if (didSwap) didSwap = false;
		else shouldSort = false;
	}
}

vector<MatchImage*> DoSearch(LargeImage* largeImage, Image* search, int n) {
	cout << "Searching..." << endl;

	MatchData bestMatch = MatchData();
	vector<MatchData*> matches;

	for (int x = 0; x < largeImage->width - search->width; x++) {
		for (int y = 0; y < largeImage->height - search->height; y++) {
			double comparison = CompareImages(largeImage, search, x, y);
			MatchData* currentMatch = new MatchData(x, y, comparison);

			matches.push_back(currentMatch);

			if (matches.size() > n) {
				BubbleSort(matches);
				matches.pop_back();
			}
		}
	}

	vector<MatchImage*> matchImages;
	vector<MatchData*>::iterator it;

	for (it = matches.begin(); it < matches.end(); it++) {
		MatchImage* result = largeImage->CreatePartial(search->width, search->height, (*it)->x, (*it)->y);
		matchImages.push_back(result);
	}

	cout << "got here" << endl;
	for (it = matches.begin(); it < matches.end(); it++) {
		delete (*it);
	}
	matches.clear();

	cout << "Done Searching." << endl;
	return matchImages;
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
