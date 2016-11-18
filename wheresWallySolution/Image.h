#ifndef image_h
#define image_h

class Image {
public:
	// Variables
	int width;
	int height;
	int count;
	int length;

	// Methods
	int getValue(int i) {
		return matrix[i];
	}
	int getValue(int x, int y) {
		return matrix[x + (y * width)];
	}
	void setValue(int i, int val) {
		matrix[i] = boundValue(val);
	}
	void setValue(int x, int y, int val) {
		matrix[x + (y * width)] = boundValue(val);
	}
	int boundValue(int val) {
		if (val > 255) {
			return 255;
		}
		else if (val < 0) {
			return 0;
		}
		else {
			return val;
		}
	}
	void fill(int val) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				matrix[x + (y * width)] = 0;
			}
		}
	}
	void print() {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				std::cout << matrix[x + (y * width)] << " ";
			}
			std::cout << std::endl;
		}
	}
	void debugPrint() {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				std::cout << matrix[x + (y * width)] << " ";
			}
			std::cout << std::endl;
		}

		std::cout << "Count: " << count << std::endl;
		std::cout << "Length: " << length << std::endl;
	}

	// Constructors
	Image() {
		std::cout << "Initialised Empty Image." << std::endl;
	}
	Image(int width, int height) {
		this->width = width;
		this->height = height;

		initialiseMatrix(this->width, this->height);
		fill(0);
	}

protected:
	double* matrix;
	void initialiseMatrix(int width, int height) {
		count = width * height;
		length = count - 1;

		matrix = new double[count];
	}
};

#endif

