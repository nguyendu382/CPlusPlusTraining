#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Vehicle {
protected:
	string& brand;
	int year;
public:
	//Vehicle() : brand("Unknown"), year(0) {}
	Vehicle(string& b, int y) : brand(b), year(y) {}
	virtual void displayInfo() const = 0;
	virtual ~Vehicle() {}
};

class Car : public Vehicle {
	int numberofDoors;
public:
	Car(string& b, int y, int d) : numberofDoors(d), Vehicle(b, y) {
		
	}
	void displayInfo() const override {
		cout << "Car Brand: " << brand << ", Year: " << year << ", Doors: " << numberofDoors << endl;
	}
};

class Truck : public Vehicle {
	double maxLoad;
public:
	Truck(string& b, int y, double pc) : maxLoad(pc), Vehicle(b, y) {
		
	}
	void displayInfo() const override {
		cout << "Truck Brand: " << brand << ", Year: " << year << ", Max load: " << maxLoad << " tons" << endl;
	}
};

class Garage {
		vector<shared_ptr<Vehicle>> vehicles;
public:
	void addVehicle(shared_ptr<Vehicle> vehicle) {
		vehicles.push_back(move(vehicle));
	}
	void displayVehicles() const {
		for (auto vehicle : vehicles) {
			vehicle->displayInfo();
		}
	}
};

int main() {
	Garage garage;
	std::string name = "Toyota";
	garage.addVehicle(make_shared<Car>(name, 2023, 5));
	garage.addVehicle(make_shared<Truck>(name, 2018, 10.5));
	garage.displayVehicles();
	return 0;
}
