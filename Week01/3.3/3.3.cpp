#include <iostream>
using namespace std;

unsigned long long factorial(int n) {
	int fac=1;
	for (int i = 2 : n) {
		fac *= i;
	}
	return fac;
}

int main() {
	int n;
	cout << "n=";
	cin >> n;
	cout << "Factorial is " << factorial(n);
	return 0;
}