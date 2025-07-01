#include <iostream>
#include <vector>
#include <optional>

template<typename T>
std::optional<T>findMax(const std::vector<T>& data ) {
	if (data.empty()) {
		return std::nullopt; 
	}
	T max = data[0]; 
	for (const auto& it : data) {
		if (it > max) max = it;
	}
	return max; 
}

int main() {
	std::vector<int> numbers = { 3, 1, 7, 2 };
	auto maxNumber = findMax(numbers);
	if (maxNumber) {
		std::cout << "Maximum element: " << *maxNumber << std::endl; 
	} else {
		std::cout << "The vector is empty." << std::endl; 
	}
	std::vector<std::string> names = {};
	auto maxName = findMax(names);
	if (maxName) {
		std::cout << "Maximum name: " << *maxName << std::endl; 
	} else {
		std::cout << "The vector is empty." << std::endl; 
	}
	return 0;
}