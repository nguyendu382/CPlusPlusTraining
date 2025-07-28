#pragma once
#include <string>
#include <list>
#include <stack>
#include "Ticket.h"

class User {
public:
    std::string name;
    //std::string userName;
    //std::string name;
    std::string email;
    std::list<Ticket> myTickets;
    std::stack<Ticket> undoStack;

    User() = default;
    User(const std::string& n, const std::string& e)
        : name(n), email(e) {}

    void bookTicket(const Ticket& t) {
        myTickets.push_back(t);
        undoStack.push(t);
    }

    bool cancelTicket(int ticketId) {
        for (auto it = myTickets.begin(); it != myTickets.end(); ++it) {
            if (it->id == ticketId) {
                myTickets.erase(it);
                return true;
            }
        }
        return false;
    }

    bool undoLastBooking() {
        if (undoStack.empty()) return false;
        Ticket last = undoStack.top();
        undoStack.pop();
        return cancelTicket(last.id);
    }

    void printTicketsForUser() const {
        if (myTickets.empty()) {
            std::cout << "No tickets booked.\n";
            return;
        }
        std::cout << "User: " << name << " | Email: " << email << "\n";
        for (const auto& t : myTickets) {
            std::cout << "Ticket ID: " << t.id
                << " | Event: " << t.eventName
                << " | Date: " << t.eventDate
                << " | Price: " << t.price << "\n";
        }
    }
};
