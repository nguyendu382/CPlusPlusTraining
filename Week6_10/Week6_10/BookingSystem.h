#pragma once
#include <unordered_map>
#include <map>
#include "User.h"
#include "Event.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <fstream>

class BookingSystem {
    //std::vector<Ticket> tickets;
    std::unordered_map<std::string, User> userMap;
    std::map<int, Event> eventMap;
    int nextTicketId = 1000;

public:
    ~BookingSystem() {
        for (auto& pair : eventMap) {
			saveEventToJson(pair.second,"event.json");
        }
    }
    bool userExists(const std::string& userName) const {
        return userMap.find(userName) != userMap.end();
    }

    void createUser(const std::string& userName, const std::string& email) {
        userMap[userName] = User(userName, email);
    }

    void addEvent(int id, const std::string& name, const std::string& date, const std::string& loc) {
        eventMap[id] = Event(id, name, date, loc);
        std::cout << "Event added: " << name << "\n";
    }

    void removeEvent(int id) {
        if (eventMap.erase(id)) {
            std::cout << "Event removed.\n";
        }
        else {
            std::cout << "Event not found.\n";
        }
    }

    void showEvents() {
        if (eventMap.empty()) {
            std::cout << "No events available.\n";
            return;
        }
        for (auto it = eventMap.begin(); it != eventMap.end(); ++it) {
            int id = it->first;
            Event& ev = it->second;
            std::cout << "[ID: " << id << "] " << ev.name << " - " << ev.date << " - " << ev.location << "\n";
        }
    }

    void showTicketsForEvent(int eventId) {
        auto it = eventMap.find(eventId);
        if (it == eventMap.end()) {
            std::cout << "Event not found.\n";
            return;
        }

        it->second.printTicketsForEvent();
    }

    void showRecentBookingsForEvent(int eventId) const {
        auto it = eventMap.find(eventId);
        if (it == eventMap.end()) {
            std::cout << "Event not found.\n";
            return;
        }

        std::cout << "Recent bookings for event: " << it->second.name << "\n";
        it->second.bookingCache.showRecentBookings();
    }

    void undoLastEventBooking(int eventId) {
        auto it = eventMap.find(eventId);
        if (it == eventMap.end()) {
            std::cout << "Event not found.\n";
            return;
        }

        Event& ev = it->second;
        if (!ev.bookingCache.hasBooking()) {
            std::cout << "No recent bookings to undo for this event.\n";
            return;
        }

        Ticket last = ev.bookingCache.getLastBooking();
        std::cout << "Last ticket booked for this event:\n";
        std::cout << "Ticket ID: " << last.id
            << " | User: " << last.userName
            << " | Price: " << last.price << "\n";

        std::cout << "Are you sure you want to remove this booking? (y/n): ";
        char confirm;
        std::cin >> confirm;

        if (confirm == 'y') {
            if (ev.undoLastBooking()) {
                std::cout << "Last booking removed from event.\n";

                if (userMap.count(last.userName)) {
                    userMap[last.userName].cancelTicket(last.id);
                }
            }
            else {
                std::cout << "Undo failed.\n";
            }
        }
        else {
            std::cout << "Undo canceled.\n";
        }
    }


    void bookTicket(const std::string& userName, int eventId, double price) {
        if (eventMap.find(eventId) == eventMap.end()) {
            std::cout << "Event not found.\n";
            return;
        }
        Ticket t(nextTicketId++, userName, eventMap[eventId].name, eventMap[eventId].date, price);

        if (!eventMap[eventId].addTicket(t)) {
            std::cout << "Ticket already booked.\n";
            return;
        }

        userMap[userName].bookTicket(t);
        std::cout << "Ticket booked successfully! ID: " << t.id << "\n";
    }


    void cancelTicket(const std::string& userName, int ticketId) {
        if (!userMap[userName].cancelTicket(ticketId)) {
            std::cout << "Ticket not found.\n";
            return;
        }
        for (auto it = eventMap.begin(); it != eventMap.end(); ++it) {
            int id = it->first;
            Event& ev = it->second;
            ev.removeTicket(ticketId);
        }
        std::cout << "Ticket canceled.\n";
    }

    void undoLastBooking(const std::string& userName) {
        User& user = userMap[userName];
        if (user.undoStack.empty()) {
            std::cout << "No booking to undo.\n";
            return;
        }

        const Ticket& last = user.undoStack.top();
        std::cout << "Last ticket booked:\n";
        std::cout << "Ticket ID: " << last.id
            << " | Event: " << last.eventName
            << " | Date: " << last.eventDate
            << " | Price: " << last.price << "\n";

        std::cout << "Are you sure you want to undo this booking? (y/n): ";
        char confirm;
        std::cin >> confirm;

        if (confirm == 'y') {
            if (user.undoLastBooking()) {
                std::cout << "Last booking undone.\n";
                for (auto it = eventMap.begin(); it != eventMap.end(); ++it) {
                    int id = it->first;
                    Event& ev = it->second;
                    ev.removeTicket(last.id);
                }
            }
            else {
                std::cout << "Undo failed.\n";
            }
        }
        else {
            std::cout << "Undo canceled.\n";
        }
    }

    void showUserTickets(const std::string& userName) {
        userMap[userName].printTicketsForUser();
    }

    void saveEventToJson(const Event& event, const std::string& filename) {
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

        doc.AddMember("eventId", event.eventId, allocator);
        doc.AddMember("name", rapidjson::Value(event.name.c_str(), allocator), allocator);
        doc.AddMember("date", rapidjson::Value(event.date.c_str(), allocator), allocator);
        doc.AddMember("location", rapidjson::Value(event.location.c_str(), allocator), allocator);

        // Tickets array
        rapidjson::Value ticketsArr(rapidjson::kArrayType);
        for (const auto& ticket : event.tickets) {
            rapidjson::Value ticketObj(rapidjson::kObjectType);
            ticketObj.AddMember("id", ticket.id, allocator);
            ticketObj.AddMember("userName", rapidjson::Value(ticket.userName.c_str(), allocator), allocator);
            ticketObj.AddMember("eventName", rapidjson::Value(ticket.eventName.c_str(), allocator), allocator);
            ticketObj.AddMember("eventDate", rapidjson::Value(ticket.eventDate.c_str(), allocator), allocator);
            ticketObj.AddMember("price", ticket.price, allocator);
            ticketsArr.PushBack(ticketObj, allocator);
        }
        doc.AddMember("tickets", ticketsArr, allocator);

        // Ghi ra file
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);

        std::ofstream ofs(filename);
        ofs << buffer.GetString();
        ofs.close();
    }
};
