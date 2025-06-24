#include <iostream>
#include <memory>
using namespace std;

class Rectangle {
	double width;
	double height;
public:
	Rectangle(double w=1, double h=1) : width(w), height(h) {}
	double area() const {
		return width * height;
	}
	double perimeter() const {
		return 2 * (width + height);
	}
	void resize(double scale) {
		width *= scale;
		height *= scale;
	}
	friend ostream& operator<<(ostream& os, const Rectangle& rect) {
		os << "Rectangle(width: " << rect.width << ", height: " << rect.height << ")";
		return os;
	}
};

int main() {
	Rectangle rect(3, 4);
	cout << rect << endl;
	cout << "Area: " << rect.area() << endl;
	cout << "Perimeter: " << rect.perimeter() << endl;
	rect.resize(3);
	cout << "After resizing:" << endl;
	cout << rect << endl;
	cout << "Area: " << rect.area() << endl;
	cout << "Perimeter: " << rect.perimeter() << endl;
	return 0;
}