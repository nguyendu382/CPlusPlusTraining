#pragma once
#include <string>

class Event {
	int eventId;
	std::string eventName;
	std::string date;
	std::string location;
	bool status;
public:
	Event(int id = 0, const std::string& name = "", const std::string& dateStr = "", const std::string& loc = "", bool stat = true)
		: eventId(id), eventName(name), date(dateStr), location(loc), status(stat) {
	}

	int getEventId() const { return eventId; }
	const std::string& getEventName() const { return eventName; }
	const std::string& getDate() const { return date; }
	const std::string& getLocation() const { return location; }
	bool isActive() const { return status; }
	void setEventId(int id) { eventId = id; }
	void setEventName(const std::string& name) { eventName = name; }
	void setDate(const std::string& dateStr) { date = dateStr; }
	void setLocation(const std::string& loc) { location = loc; }
	void setStatus(bool stat) { status = stat; }
};