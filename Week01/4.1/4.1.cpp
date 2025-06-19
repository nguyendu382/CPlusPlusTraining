#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> v = { 1,2,3,4,5,6,7,8,9,10 }; // Initialize a vector of size 10 with all elements set to 0
	for (auto i : v) {
		cout << i << " "; // Print each element
	}
	return 0;
}