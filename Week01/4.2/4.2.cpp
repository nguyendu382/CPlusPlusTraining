#include <iostream>
using namespace std;

enum class Gender { Male, Female, Other };

string to_string(Gender gender) {
	switch (gender) {
	case Gender::Male: return "Male";
	case Gender::Female: return "Female";
	case Gender::Other: return "Other";
	default: return "Unknown";
	}
}
void printGender(Gender gender) {
	cout << "Gender: " << to_string(gender) << endl;
}
int main() {
	printGender(Gender::Male);
	printGender(Gender::Female);
	printGender(Gender::Other);
}