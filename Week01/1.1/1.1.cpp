#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int a, b;
	cout << "A=";
	cin >> a;
	cout << "B=";
	cin >> b;
	cout << "Sum: " << a + b << endl;
	cout << "Diff: " << abs(a - b) << endl;
	cout << "Product: " << a * b << endl;
	cout << "Quotient: " << ((a > b) ? (a / b) : (b / a));
	return 0;
}