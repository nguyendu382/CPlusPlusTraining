#include <iostream>
using namespace std;

class Student {
	public:
	string name;
	int age;
};

int main() {
	shared_ptr<Student> st1 = make_shared<Student>();
	st1->name = "Son";
	st1->age = 23;
	shared_ptr<Student> st2 = st1;
	cout << "Name: " << st1->name << ", Age: " << st1->age << endl;
	cout << "Shared ownership count: " << st1.use_count() << endl;
	return 0;

}