#ifndef image_h
#define image_h

class Image {
public:
	int width;
	int height;
	Image(int width, int height) {
		this->width = width;
		this->height = height;

		// assign matrix here
	}
	int getValue(int x, int y) {
		return matrix[x + (y * width)];
	}
private:
	int* matrix;
	int boundValue(int val) {
		if (val > 255) {
			return 255;
		} else if (val < 0) {
			return 0;
		} else {
			return val;
		}
	}
};

#endif

