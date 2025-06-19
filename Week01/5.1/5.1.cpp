#include <iostream>
using namespace std;

int main() {
	unique_ptr<int> ptr = make_unique<int>(10);
	cout << "Value: " << *ptr << endl; // Output: Value: 10
	return 0;
}