#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Shape {
public:
	virtual double area() const = 0; 
	virtual ~Shape() {} 
};

class Circle : public Shape {
	double radius;
public:
	Circle(double r) : radius(r) {}
	double area() const override {
		return 3.14159 * radius * radius;
	}
};

class Rectangle : public Shape {
	double width, height;
public:
	Rectangle(double w, double h) : width(w), height(h) {}
	double area() const override {
		return width * height;
	}
};

class Triangle : public Shape {
	double base, height;
public:
	Triangle(double b, double h) : base(b), height(h) {}
	double area() const override {
		return 0.5 * base * height;
	}
};

int main() {
	vector<shared_ptr<Shape>> shapes;
	shapes.push_back(make_shared<Circle>(3));
	shapes.push_back(make_shared<Rectangle>(4, 6));
	shapes.push_back(make_shared<Triangle>(7, 4));
	for (const auto& shape : shapes) {
		cout << "Area: " << shape->area() << endl;
	}
	double totalArea = 0;
	for (const auto& shape : shapes) {
		totalArea += shape->area();
	}
	cout << "Total Area: " << totalArea << endl;
	return 0;
}