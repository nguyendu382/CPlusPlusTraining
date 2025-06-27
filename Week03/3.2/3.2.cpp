#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Vehicle {
protected:
	string brand;
	int year;
public:
	Vehicle() : brand("Unknown"), year(0) {}
	Vehicle(const string& b, int y) : brand(b), year(y) {}
	virtual void displayInfo() const = 0;
	virtual ~Vehicle() {}
};

class Car : public Vehicle {
	int numberofDoors;
public:
	Car(const string& b, int y, int d) : numberofDoors(d) {
		brand = b;
		year = y;
	}
	void displayInfo() const override {
		cout << "Car Brand: " << brand << ", Year: " << year << ", Doors: " << numberofDoors << endl;
	}
};

class Truck : public Vehicle {
	double maxLoad;
public:
	Truck(const string& b, int y, double pc) : maxLoad(pc) {
		brand = b;
		year = y;
	}
	void displayInfo() const override {
		cout << "Truck Brand: " << brand << ", Year: " << year << ", Max load: " << maxLoad << " tons" << endl;
	}
};

class Garage {
		vector<unique_ptr<Vehicle>> vehicles;
public:
	void addVehicle(unique_ptr<Vehicle> vehicle) {
		vehicles.push_back(move(vehicle));
	}
	void displayVehicles() const {
		for (const auto& vehicle : vehicles) {
			vehicle->displayInfo();
		}
	}
};

int main() {
	Garage garage;
	garage.addVehicle(make_unique<Car>("Vinfast", 2023, 5));
	garage.addVehicle(make_unique<Truck>("Ford", 2018, 10.5));
	garage.displayVehicles();
	return 0;
}
