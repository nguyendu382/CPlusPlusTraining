#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	bool p = true;
	cout << "Number=";
	cin >> n;
	if (n <= 1) p = false;
	else {
		for (int i = 2; i <= sqrt(n); i++) {
			if (n % i == 0) {
				p = false;
				break;
			}
		}
	}
	if (p) cout << "A prime number";
	else cout << "Not a prime number";
	return 0;
}