#pragma once
#include <string>

struct Ticket {
    int id;
	std::string userName;
	int eventId;
	double price;
	bool status;
	
	Ticket(int i = 0, const std::string& u = "", int eId = 0, double p = 0.0, bool s = true)
		: id(i), userName(u), eventId(eId), price(p), status(s) {}

	int getId() const { return id; }
	const std::string& getUserName() const { return userName; }
	int getEventId() const { return eventId; }
	double getPrice() const { return price; }
	bool isValid() const { return status; }
	void setId(int i) { id = i; }
	void setUserName(const std::string& u) { userName = u; }
	void setEventId(int eId) { eventId = eId; }
	void setPrice(double p) { price = p; }
	void setStatus(bool s) { status = s; }
};