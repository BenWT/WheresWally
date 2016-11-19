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
	double* getMatrix() {
		return matrix;
	}
	double getValue(int i) {
		return matrix[i];
	}
	double getValue(int x, int y) {
		return matrix[x + (y * width)];
	}
	void setValue(int i, double val) {
		matrix[i] = boundValue(val);
	}
	void setValue(int x, int y, double val) {
		matrix[x + (y * width)] = boundValue(val);
	}
	double boundValue(double val) {
		if (val > 255) {
			return 255.0;
		}
		else if (val < 0) {
			return 0.0;
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

	// Constructors
	Image() {
		std::cout << "Initialised Empty Image." << std::endl;
	}
	Image(int width, int height) {
		this->width = width;
		this->height = height;

		initialiseMatrix();
		fill(0);
	}
	Image(int width, int height, double* matrix) {
		this->width = width;
		this->height = height;

		initialiseMatrix(matrix);
	}

protected:
	double* matrix;
	void initialiseMatrix() {
		count = width * height;
		length = count - 1;

		matrix = new double[count];
	}
	void initialiseMatrix(double* matrix) {
		count = width * height;
		length = count - 1;

		this->matrix = matrix;
	}
};

#endif

