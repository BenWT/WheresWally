#include <iostream>
#include "Image.h"
#include "FullImage.h"
#include "PartialImage.h"

#define WIDTH 4
#define HEIGHT 3

int main()
{
	PartialImage image(WIDTH, HEIGHT);
	
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			image.setValue(x, y, x + (y * WIDTH) + 1);
		}
	}

	image.debugPrint();

	int* newRow = new int[WIDTH];
	for (int i = 0; i < WIDTH; i++) {
		newRow[i] = i + 13;
	}

	image.addRow(newRow);
	image.debugPrint();
	
	// image load code
	// search code
	// save code

	return 0;
}