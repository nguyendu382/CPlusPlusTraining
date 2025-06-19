#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	a = a + b;
	b = a - b;
	a = a - b;
	cout << "After swap:";
	cout << "\na=" << a;
	cout << "\nb=" << b;
}

int main() {
	int a, b;
	cout << "Before swap:\n";
	cout << "a=";
	cin >> a;
	cout << "b=";
	cin >> b;
	swap(a, b);
	return 0;
}