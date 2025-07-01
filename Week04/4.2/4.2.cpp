#include <iostream>
#include "Math.h"

int main() {
	Math<int> calc;
	int a = 5, b = 3;
	auto sum = calc.add(a, b);
	std::cout << "Sum: " << sum << std::endl;
	auto diff = calc.sub(a, b);
	std::cout << "Difference: " << diff << std::endl;
	auto product = calc.mul(a, b);
	std::cout << "Product: " << product << std::endl;
	auto quotient = calc.div(a, b);
	if (quotient) {
		std::cout << "Quotient: " << *quotient << std::endl;
	} else {
		std::cout << "Division by zero is not allowed." << std::endl;
	}
	auto result = calc.div(10, 0);
	if (result) {
		std::cout << "Result: " << *result << std::endl;
	} else {
		std::cout << "Division by zero is not allowed." << std::endl;
	}
	return 0;
}