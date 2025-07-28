#pragma once
#include <rapidjson/document.h>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "Ticket.h"
#include "BookingCache.h"

class Event {
public:
    int eventId;
    std::string name;
    std::string date;
    std::string location;
    std::vector<Ticket> tickets;
    std::set<int> bookedTicketIds;
    BookingCache bookingCache;
    //bool status;

    Event() = default;
    Event(int id, const std::string& n, const std::string& d, const std::string& l)
        : eventId(id), name(n), date(d), location(l) {}

    bool addTicket(const Ticket& ticket) {
        if (bookedTicketIds.count(ticket.id)) return false;
        tickets.push_back(ticket);
        bookedTicketIds.insert(ticket.id);
        bookingCache.addBooking(ticket);
        return true;
    }


    bool removeTicket(int ticketId) {
        for (auto it = tickets.begin(); it != tickets.end(); ++it) {
            if (it->id == ticketId) {
                tickets.erase(it);
                bookedTicketIds.erase(ticketId);
                return true;
            }
        }
        return false;
    }

    bool undoLastBooking() {
        if (!bookingCache.hasBooking()) return false;

        Ticket last = bookingCache.getLastBooking();
        bookingCache.removeLastBooking();
        return removeTicket(last.id);
    }


    void sortTicketsByPrice() {
        std::sort(tickets.begin(), tickets.end(),
            [](const Ticket& a, const Ticket& b) {
                return a.price > b.price;
            });
    }

    void printTicketsForEvent() {
        if (tickets.empty()) {
            std::cout << "No tickets booked for this event.\n";
            return;
        }

        sortTicketsByPrice();

        std::cout << "Tickets for event: " << name << " on " << date << "\n";
        for (const auto& t : tickets) {
            std::cout << "Ticket ID: " << t.id
                << " | User: " << t.userName
                << " | Price: " << t.price << "\n";
        }
    }
};
