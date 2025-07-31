#pragma once
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm> 
#include "User.h"
#include "Event.h"
#include "Ticket.h"
#include "BookingCache.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

class BookingSystem {
    std::vector<Ticket> tickets;
    std::unordered_map<std::string, User> users;
    std::map<int, Event> events;
    std::set<int> eventIds;
    std::map<int, BookingCache> bookingCaches;
    int nextTicketId = 1000;

    static void sortTicketsByPrice(std::vector<Ticket>& ticketList) {
        std::sort(ticketList.begin(), ticketList.end(),
            [](const Ticket& a, const Ticket& b) {
                return a.getPrice() > b.getPrice();
            });
    }

public:
    bool userExists(const std::string& userName) const;

    void createUser(const std::string& userName, const std::string& name);

    void addEvent(int id, const std::string& name, const std::string& date, const std::string& loc);

    void updateEvent(int id);


    void removeEvent(int id);

    void activateEvent(int id);

    void bookTicket(const std::string& userName, int eventId, double price);

    void cancelTicket(const std::string& userName, int ticketId);

    void undoLastBooking(const std::string& userName);

    void undoLastEventBooking(int eventId);

    void showUserTickets(const std::string& userName);

    void showTicketsForEvent(int eventId);

    void showEvents();

    void showRecentBookingsForEvent(int eventId);

    void saveToJson(const std::string& filename);

    void loadFromJson(const std::string& filename);
};
