#include "BookingSystem.h"

 bool BookingSystem::userExists(const std::string& userName) const {
    return m_users.count(userName);
}

 void BookingSystem::createUser(const std::string& userName, const std::string& name) {
    User user;
    user.setUserName(userName);
    user.setName(name);
    m_users[userName] = user;
}

void BookingSystem::addEvent(const std::string& name, const std::string& date, const std::string& loc) {
   
    Event e(nextEventId++, name, date, loc);
	m_events[e.getEventId()] = e;
    m_bookingCaches[e.getEventId()] = BookingCache();
    std::cout << "Event added successfully: " << name << std::endl;
}

  void BookingSystem::updateEvent(int id) {
     if (!m_events.count(id)) {
         std::cout << "Event ID not found.\n";
         return;
     }

     Event& e = m_events[id];

     std::cout << "\n--- Current Event Information ---\n";
     std::cout << "ID: " << e.getEventId()
         << " | Name: " << e.getEventName()
         << " | Date: " << e.getDate()
         << " | Location: " << e.getLocation()
         << " | Status: " << (e.isActive() ? "Active" : "Inactive") << "\n";

     std::string newName, newDate, newLocation;

     std::cout << "\n--- Enter New Information ---\n";
     std::cout << "New Name: ";
     std::cin >> newName;
     std::cout << "New Date: ";
     std::cin >> newDate;
     std::cout << "New Location: ";
     std::cin >> newLocation;

     e.setEventName(newName);
     e.setDate(newDate);
     e.setLocation(newLocation);

     std::cout << "Event updated successfully.\n";
 }

  void BookingSystem::removeEvent(int id) {
     auto it = m_events.find(id);
     if (it == m_events.end()) {
         std::cout << "Event not found.\n";
         return;
     }
     it->second.setStatus(false);
     for (auto& t : m_tickets) {
         if (t.getEventId() == id && t.isValid()) {
             t.setStatus(false);
         }
     }
     std::cout << "Event and all related tickets have been deactivated.\n";
 }

   void BookingSystem::activateEvent(int id) {
      auto it = m_events.find(id);
      if (it == m_events.end()) {
          std::cout << "Event not found.\n";
          return;
      }
      if (it->second.isActive()) {
          std::cout << "Event is already active.\n";
          return;
      }
      it->second.setStatus(true);
      for (auto& t : m_tickets) {
          if (t.getEventId() == id && !t.isValid()) {
              t.setStatus(true);
          }
      }
      std::cout << "Event and all related tickets have been activated.\n";
  }

   void BookingSystem::bookTicket(const std::string& userName, int eventId, double price) {
      if (!m_users.count(userName) || !m_events.count(eventId)) {
          std::cout << "User or Event not found.\n";
          return;
      }

	  Ticket t(nextTicketId++, userName, eventId, price);
      m_tickets.push_back(t);
      m_bookingCaches[eventId].addBooking(t.id);
      std::cout << "Ticket booked successfully. ID: " << t.getId() << "\n";
  }

   void BookingSystem::cancelTicket(const std::string& userName, int ticketId) {
      for (auto& t : m_tickets) {
          if (t.getId() == ticketId && t.getUserName() == userName && t.isValid()) {
              t.setStatus(false);
              std::cout << "Ticket canceled.\n";
              return;
          }
      }
      std::cout << "Ticket not found or already canceled.\n";
  }

   void BookingSystem::undoLastBooking(const std::string& userName) {
      for (auto it = m_tickets.rbegin(); it != m_tickets.rend(); ++it) {
          if (it->getUserName() == userName && it->isValid()) {
              std::cout << "Undo booking? Ticket ID: " << it->getId()
                  << " | Event ID: " << it->getEventId()
                  << " | Price: " << it->getPrice() << "\n";
              std::cout << "Undo? (y/n): ";
              char c;
              std::cin >> c;
              if (c == 'y') {
                  it->setStatus(false);
                  m_bookingCaches[it->getEventId()].removeLastBooking();
                  std::cout << "Undo ticket ID: " << it->getId() << "\n";
              }
              else std::cout << "Undo canceled.\n";
              return;
          }
      }
      std::cout << "No booking to undo.\n";
  }

   void BookingSystem::undoLastEventBooking(int eventId) {
      if (!m_events.count(eventId) || !m_bookingCaches.count(eventId)) {
          std::cout << "Event not found.\n";
          return;
      }
      for (auto it = m_tickets.rbegin(); it != m_tickets.rend(); ++it) {
          if (it->getEventId() == eventId && it->isValid()) {
              std::cout << "Undo booking? Ticket ID: " << it->getId()
                  << " | User: " << it->getUserName()
                  << " | Price: " << it->getPrice() << "\n";
              std::cout << "Undo? (y/n): ";
              char c;
              std::cin >> c;
              if (c == 'y') {
                  it->setStatus(false);
                  m_bookingCaches[eventId].removeLastBooking();
                  std::cout << "Last booking removed.\n";
              }
              else std::cout << "Undo canceled.\n";
              return;
          }
      }
      std::cout << "No booking to undo for this event.\n";
  }

void BookingSystem::showUserTickets(const std::string& userName) {
    int sum = 0;
    for (const auto& t : m_tickets) {
        if (t.getUserName() == userName) {
            std::cout << "Ticket ID: " << t.getId()
                << " | Event ID: " << t.getEventId()
                << " | Price: " << t.getPrice()
                << " | Status: " << (t.isValid() ? "Valid" : "Cancelled") << "\n";
            sum++;
        }
    }
    if (sum == 0) {
        std::cout << "No booking for this event.\n";
    }
    else {
        std::cout << "Total tickets: " << sum << "\n";
    }
}

void BookingSystem::showTicketsForEvent(int eventId) {
    if (!m_events.count(eventId) || !m_bookingCaches.count(eventId)) {
        std::cout << "Event not found.\n";
        return;
    }
    std::vector<Ticket> eventTickets;
    for (const auto& t : m_tickets) {
        if (t.getEventId() == eventId) {
            eventTickets.push_back(t);
        }
    }
    if (eventTickets.empty()) {
        std::cout << "No booking for this event.\n";
        return;
    }
    sortTicketsByPrice(eventTickets);
    int sum = 0;
    for (const auto& t : eventTickets) {
        std::cout << "Ticket ID: " << t.getId()
            << " | User: " << t.getUserName()
            << " | Price: " << t.getPrice()
            << " | Status: " << (t.isValid() ? "Valid" : "Cancelled") << "\n";
        sum++;
    }
    std::cout << "Total tickets: " << sum << "\n";
}

void BookingSystem::showEvents() {
    int sum = 0;
    for (const auto& eventPair : m_events) {
        const int id = eventPair.first;
        const Event& e = eventPair.second;
        std::cout << "[ID: " << e.getEventId() << "] "
            << e.getEventName() << " - " << e.getDate()
            << " - " << e.getLocation() << " - "
            << (e.isActive() ? "Active" : "Inactive") << "\n";
        sum++;
    }
    std::cout << "Total events: " << sum << "\n";
}

 void BookingSystem::showRecentBookingsForEvent(int eventId) {
    if (m_events.count(eventId) && m_bookingCaches.count(eventId))
        for(const auto& booking : m_bookingCaches[eventId].getRecentBookings()) {
            for(const auto& t : m_tickets) {
                if (t.getId() == booking) {
                    std::cout << "Recent Booking ID: " << t.getId()
                        << " | User: " << t.getUserName()
                        << " | Price: " << t.getPrice()
                        << " | Status: " << (t.isValid() ? "Valid" : "Cancelled") << "\n";
                }
			}
		}
    else std::cout << "No recent bookings for this event.\n";
}

 void BookingSystem::saveToJson(const std::string& filename) {
    rapidjson::Document doc;
    doc.SetObject();
    auto& allocator = doc.GetAllocator();

    // Save events
    rapidjson::Value eventArr(rapidjson::kArrayType);
    for (const auto& pair : m_events) {
        const auto& e = pair.second;
        rapidjson::Value eventObj(rapidjson::kObjectType);
        eventObj.AddMember("eventId", e.getEventId(), allocator);
        eventObj.AddMember("eventName", rapidjson::Value(e.getEventName().c_str(), allocator), allocator);
        eventObj.AddMember("date", rapidjson::Value(e.getDate().c_str(), allocator), allocator);
        eventObj.AddMember("location", rapidjson::Value(e.getLocation().c_str(), allocator), allocator);
        eventObj.AddMember("status", e.isActive(), allocator);
        eventArr.PushBack(eventObj, allocator);
    }
    doc.AddMember("events", eventArr, allocator);

    // Save users
    rapidjson::Value userArr(rapidjson::kArrayType);
    for (const auto& pair : m_users) {
        const auto& u = pair.second;
        rapidjson::Value userObj(rapidjson::kObjectType);
        userObj.AddMember("userName", rapidjson::Value(u.getUserName().c_str(), allocator), allocator);
        userObj.AddMember("name", rapidjson::Value(u.getName().c_str(), allocator), allocator);
        userArr.PushBack(userObj, allocator);
    }
    doc.AddMember("users", userArr, allocator);

    // Save tickets
    rapidjson::Value ticketArr(rapidjson::kArrayType);
    for (const auto& t : m_tickets) {
        rapidjson::Value ticketObj(rapidjson::kObjectType);
        ticketObj.AddMember("id", t.getId(), allocator);
        ticketObj.AddMember("userName", rapidjson::Value(t.getUserName().c_str(), allocator), allocator);
        ticketObj.AddMember("eventId", t.getEventId(), allocator);
        ticketObj.AddMember("price", t.getPrice(), allocator);
        ticketObj.AddMember("status", t.isValid(), allocator);
        ticketArr.PushBack(ticketObj, allocator);
    }
    doc.AddMember("tickets", ticketArr, allocator);

    // Write to file
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

    doc.Accept(writer);

    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        ofs << buffer.GetString();
        ofs.close();
        std::cout << "Saved to " << filename << " successfully.\n";
    }
    else {
        std::cout << "Failed to open file " << filename << "\n";
    }
}

 void BookingSystem::loadFromJson(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cout << "Failed to open file " << filename << "\n";
        return;
    }

    std::string jsonStr((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();

    rapidjson::Document doc;
    if (doc.Parse(jsonStr.c_str()).HasParseError()) {
        std::cout << "Failed to parse JSON.\n";
        return;
    }

    // Clear current data
    m_tickets.clear();
    m_users.clear();
    m_events.clear();
    m_bookingCaches.clear();
    nextTicketId = 1000;
    nextEventId = 1;

    // Load events
    int maxEventId = nextEventId;
    if (doc.HasMember("events") && doc["events"].IsArray()) {
        for (const auto& eventObj : doc["events"].GetArray()) {
            if (eventObj.HasMember("eventId") && eventObj.HasMember("eventName") &&
                eventObj.HasMember("date") && eventObj.HasMember("location") && eventObj.HasMember("status")) {
                int id = eventObj["eventId"].GetInt();
                Event e;
                e.setEventId(id);
                e.setEventName(eventObj["eventName"].GetString());
                e.setDate(eventObj["date"].GetString());
                e.setLocation(eventObj["location"].GetString());
                e.setStatus(eventObj["status"].GetBool());
                m_events[id] = e;
                m_bookingCaches[id] = BookingCache();
                if (e.getEventId() >= maxEventId) {
                    maxEventId = e.getEventId() + 1;
                }
            }
        }
    }
	nextEventId = maxEventId;

    // Load users
    if (doc.HasMember("users") && doc["users"].IsArray()) {
        for (const auto& userObj : doc["users"].GetArray()) {
            if (userObj.HasMember("userName") && userObj.HasMember("name")) {
                User u;
                u.setUserName(userObj["userName"].GetString());
                u.setName(userObj["name"].GetString());
                m_users[u.getUserName()] = u;
            }
        }
    }

    // Load tickets
    int maxTicketId = nextTicketId;
    if (doc.HasMember("tickets") && doc["tickets"].IsArray()) {
        for (const auto& ticketObj : doc["tickets"].GetArray()) {
            if (ticketObj.HasMember("id") && ticketObj.HasMember("userName") &&
                ticketObj.HasMember("eventId") && ticketObj.HasMember("price") && ticketObj.HasMember("status")) {
                Ticket t;
                t.setId(ticketObj["id"].GetInt());
                t.setUserName(ticketObj["userName"].GetString());
                t.setEventId(ticketObj["eventId"].GetInt());
                t.setPrice(ticketObj["price"].GetDouble());
                t.setStatus(ticketObj["status"].GetBool());
                m_tickets.push_back(t);
                if (m_bookingCaches.count(t.getEventId())) {
                    m_bookingCaches[t.getEventId()].addBooking(t.id);
                }
                if (t.getId() >= maxTicketId) {
                    maxTicketId = t.getId() + 1;
                }
            }
        }
    }
    nextTicketId = maxTicketId;

    std::cout << "Loaded from " << filename << " successfully.\n";
}
