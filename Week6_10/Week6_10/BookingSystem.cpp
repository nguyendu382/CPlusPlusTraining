#include "BookingSystem.h"

 bool BookingSystem::userExists(const std::string& userName) const {
    return users.count(userName);
}

 void BookingSystem::createUser(const std::string& userName, const std::string& name) {
    User user;
    user.setUserName(userName);
    user.setName(name);
    users[userName] = user;
}

void BookingSystem::addEvent(int id, const std::string& name, const std::string& date, const std::string& loc) {
    if (eventIds.count(id)) {
        std::cout << "Event ID already exists. Please use a unique ID.\n";
        return;
    }
    Event e;
    e.setEventId(id);
    e.setEventName(name);
    e.setDate(date);
    e.setLocation(loc);
    e.setStatus(true);
    events[id] = e;
    eventIds.insert(id);
    bookingCaches[id] = BookingCache();
    std::cout << "Event added successfully: " << name << std::endl;
}

  void BookingSystem::updateEvent(int id) {
     if (!eventIds.count(id)) {
         std::cout << "Event ID not found.\n";
         return;
     }

     Event& e = events[id];

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
     auto it = events.find(id);
     if (it == events.end()) {
         std::cout << "Event not found.\n";
         return;
     }
     it->second.setStatus(false);
     for (auto& t : tickets) {
         if (t.getEventId() == id && t.isValid()) {
             t.setStatus(false);
         }
     }
     std::cout << "Event and all related tickets have been deactivated.\n";
 }

   void BookingSystem::activateEvent(int id) {
      auto it = events.find(id);
      if (it == events.end()) {
          std::cout << "Event not found.\n";
          return;
      }
      if (it->second.isActive()) {
          std::cout << "Event is already active.\n";
          return;
      }
      it->second.setStatus(true);
      for (auto& t : tickets) {
          if (t.getEventId() == id && !t.isValid()) {
              t.setStatus(true);
          }
      }
      std::cout << "Event and all related tickets have been activated.\n";
  }

   void BookingSystem::bookTicket(const std::string& userName, int eventId, double price) {
      if (!users.count(userName) || !eventIds.count(eventId)) {
          std::cout << "User or Event not found.\n";
          return;
      }

      Ticket t;
      t.setId(nextTicketId++);
      t.setUserName(userName);
      t.setEventId(eventId);
      t.setPrice(price);
      t.setStatus(true);

      tickets.push_back(t);
      bookingCaches[eventId].addBooking(t);
      std::cout << "Ticket booked successfully. ID: " << t.getId() << "\n";
  }

   void BookingSystem::cancelTicket(const std::string& userName, int ticketId) {
      for (auto& t : tickets) {
          if (t.getId() == ticketId && t.getUserName() == userName && t.isValid()) {
              t.setStatus(false);
              std::cout << "Ticket canceled.\n";
              return;
          }
      }
      std::cout << "Ticket not found or already canceled.\n";
  }

   void BookingSystem::undoLastBooking(const std::string& userName) {
      for (auto it = tickets.rbegin(); it != tickets.rend(); ++it) {
          if (it->getUserName() == userName && it->isValid()) {
              std::cout << "Undo booking? Ticket ID: " << it->getId()
                  << " | Event ID: " << it->getEventId()
                  << " | Price: " << it->getPrice() << "\n";
              std::cout << "Undo? (y/n): ";
              char c;
              std::cin >> c;
              if (c == 'y') {
                  it->setStatus(false);
                  bookingCaches[it->getEventId()].removeLastBooking();
                  std::cout << "Undo ticket ID: " << it->getId() << "\n";
              }
              else std::cout << "Undo canceled.\n";
              return;
          }
      }
      std::cout << "No booking to undo.\n";
  }

   void BookingSystem::undoLastEventBooking(int eventId) {
      if (!eventIds.count(eventId) || !bookingCaches.count(eventId)) {
          std::cout << "Event not found.\n";
          return;
      }
      for (auto it = tickets.rbegin(); it != tickets.rend(); ++it) {
          if (it->getEventId() == eventId && it->isValid()) {
              std::cout << "Undo booking? Ticket ID: " << it->getId()
                  << " | User: " << it->getUserName()
                  << " | Price: " << it->getPrice() << "\n";
              std::cout << "Undo? (y/n): ";
              char c;
              std::cin >> c;
              if (c == 'y') {
                  it->setStatus(false);
                  bookingCaches[eventId].removeLastBooking();
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
    for (const auto& t : tickets) {
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
    if (!eventIds.count(eventId) || !bookingCaches.count(eventId)) {
        std::cout << "Event not found.\n";
        return;
    }
    std::vector<Ticket> eventTickets;
    for (const auto& t : tickets) {
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
    for (const auto& eventPair : events) {
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
    if (eventIds.count(eventId) && bookingCaches.count(eventId))
        bookingCaches[eventId].showRecentBookings();
    else std::cout << "No recent bookings for this event.\n";
}

 void BookingSystem::saveToJson(const std::string& filename) {
    rapidjson::Document doc;
    doc.SetObject();
    auto& allocator = doc.GetAllocator();

    // Save events
    rapidjson::Value eventArr(rapidjson::kArrayType);
    for (const auto& pair : events) {
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
    for (const auto& pair : users) {
        const auto& u = pair.second;
        rapidjson::Value userObj(rapidjson::kObjectType);
        userObj.AddMember("userName", rapidjson::Value(u.getUserName().c_str(), allocator), allocator);
        userObj.AddMember("name", rapidjson::Value(u.getName().c_str(), allocator), allocator);
        userArr.PushBack(userObj, allocator);
    }
    doc.AddMember("users", userArr, allocator);

    // Save tickets
    rapidjson::Value ticketArr(rapidjson::kArrayType);
    for (const auto& t : tickets) {
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
    tickets.clear();
    users.clear();
    events.clear();
    eventIds.clear();
    bookingCaches.clear();
    nextTicketId = 1000;

    // Load events
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
                events[id] = e;
                eventIds.insert(id);
                bookingCaches[id] = BookingCache();
            }
        }
    }

    // Load users
    if (doc.HasMember("users") && doc["users"].IsArray()) {
        for (const auto& userObj : doc["users"].GetArray()) {
            if (userObj.HasMember("userName") && userObj.HasMember("name")) {
                User u;
                u.setUserName(userObj["userName"].GetString());
                u.setName(userObj["name"].GetString());
                users[u.getUserName()] = u;
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
                tickets.push_back(t);
                if (bookingCaches.count(t.getEventId())) {
                    bookingCaches[t.getEventId()].addBooking(t);
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
