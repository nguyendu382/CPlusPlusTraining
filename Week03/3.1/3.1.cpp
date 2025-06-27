#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Animal {
public:
	virtual void speak() const = 0; 
	virtual void feed() const {
		cout << "Feeding the animal." << endl;
	}
	virtual ~Animal() {} 
};

class Lion : public Animal {
public:
	void speak() const override {
		cout << "Roarrr!" << endl;
	}
	void feed() const override {
		cout << "Feeding the lion meat." << endl;
	}
	~Lion() {
		cout << "Lion bye." << endl;
	}
};

class Elephant : public Animal {
public:
	void speak() const override {
		cout << "Trumpettt!" << endl;
	}
	void feed() const override {
		cout << "Feeding the elephant grass." << endl;
	}
	~Elephant() {
		cout << "Elephant bye." << endl;
	}
};

class Monkey : public Animal {
public:
	void speak() const override {
		cout << "Ooh ooh aah aah!" << endl;
	}
	void feed() const override {
		cout << "Feeding the monkey bananas." << endl;
	}
	~Monkey() {
		cout << "Monkey bye." << endl;
	}
};

int main() {
	vector<shared_ptr<Animal>> zoo;
	zoo.push_back(make_shared<Lion>());
	zoo.push_back(make_shared<Elephant>());
	zoo.push_back(make_shared<Monkey>());
	for (const auto& animal : zoo) {
		animal->speak();
		animal->feed();
	}
	return 0;
}