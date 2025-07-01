#include <iostream>

template<typename ... Args>
auto sumAll(Args ... args) {
	return (args + ...);
}

int main() {
	int a = 1, b = 2, c = 3, d = 4;
	double x = 2.5, y = 1.5;
	std::cout << "Sum of integers: " << sumAll(a, b, c, d) << std::endl;
	std::cout << "Sum of doubles: " << sumAll(x, y) << std::endl;
	return 0;
}