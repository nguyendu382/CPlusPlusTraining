#pragma once
#include <string>

class User {
	std::string userName;
	std::string name;
public:
	User(const std::string& u = "", const std::string& n = "")
		: userName(u), name(n) {
	}

	const std::string& getUserName() const { return userName; }
	const std::string& getName() const { return name; }
	void setUserName(const std::string& u) { userName = u; }
	void setName(const std::string& n) { name = n; }
};
