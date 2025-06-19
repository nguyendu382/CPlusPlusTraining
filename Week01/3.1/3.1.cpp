#include <iostream>
using namespace std;

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int main() {
	int a, b;
	cout << "a=";
	cin >> a;
	cout << "b=";
	cin >> b;
	cout <<"Max is " << max(a, b);
	return 0;
}