#include<iostream>
using namespace std;

class Student {
public:
	string name;
	int age;
};

int main() {
	unique_ptr<Student> st1 = make_unique<Student>();
	st1->name = "Son";
	st1->age = 23;
	cout << "Name: " << st1->name << ", Age: " << st1->age << endl;
	unique_ptr<Student> st2 = move(st1); 
	cout << "After move" << endl;
	cout << "Name: " << st2->name << ", Age: " << st2->age << endl;
	return 0;
}