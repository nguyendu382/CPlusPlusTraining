#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Student {
	string name;
	int age;
	double gpa;
	static int count;
public:
	Student(string n, int a, double g) : name(n), age(a), gpa(g) { count++; }
	~Student() { count--; }
	void setName(string n) {
		name = n;
	}
	void setAge(int a) {
		age = a;
	}
	void setGPA(double g) {
		gpa = g;
	}
	string getName() const {
		return name;
	}
	int getAge() const {
		return age;
	}
	double getGPA() const {
		return gpa;
	}
	static int getCount() {
		return count;
	}
	void printfInfo() {
		cout << "Name: " << name << ", Age: " << age << ", GPA: " << gpa << endl;
	}
};
int Student::count = 0;

void addStudent(vector<shared_ptr<Student>>& list, const string& name, int age, double gpa) {
	list.push_back(make_shared<Student>(name, age, gpa));
}
void printAllStudents(const vector<shared_ptr<Student>>& list) {
	for (const auto& student : list) {
		student->printfInfo();
	}
}
double calculateAverageGPA(const vector<shared_ptr<Student>>& list) {
	double totalGPA = 0.0;
	for (const auto& student : list) {
		totalGPA += student->getGPA();
	}
	return totalGPA / list.size();
}
int main() {
	vector<shared_ptr<Student>> students;
	addStudent(students, "A", 20, 3);
	addStudent(students, "B", 22, 2);
	addStudent(students, "C", 21, 1);
	cout << "All Students:" << endl;
	printAllStudents(students);
	cout << "Average GPA: " << calculateAverageGPA(students) << endl;
	cout << "Total number of students: " << Student::getCount() << endl;
	addStudent(students, "Son", 23, 2.5);
	for (auto& student : students) {
		if (student->getName() == "Son") {
			student->setGPA(3.6);
		}
	}
	cout << "After updating Son's GPA:" << endl;
	printAllStudents(students);
	return 0;
}