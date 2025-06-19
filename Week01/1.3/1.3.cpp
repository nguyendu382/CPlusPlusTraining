#include <iostream>
using namespace std;

int main() {
	float a, b, c, x;
	cout << "Diem Toan: ";
	cin >> a;
	cout << "Diem Van: ";
	cin >> b;
	cout << "Diem Anh: ";
	cin >> c;
	x = (a + b + c) / 3;
	if (x >= 8.5) cout << "Xuat sac";
	else if (x >= 6.5) cout << "Gioi";
	else if (x >= 4) cout << "Trung binh";
	else cout << "Yeu";
	return 0;
}