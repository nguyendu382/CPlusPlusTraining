#pragma once
#include <deque>
#include <iostream>
#include "Ticket.h"

class BookingCache {
    std::deque<Ticket> recentBookings;
    //std::deque<int>
    size_t maxSize;

public:
    BookingCache(size_t size = 10) : maxSize(size) {}

    void addBooking(const Ticket& b) {
        if (recentBookings.size() >= maxSize)
            recentBookings.pop_front();
        recentBookings.push_back(b);
    }

    bool hasBooking() const {
        return !recentBookings.empty();
    }

    Ticket getLastBooking() const {
        if (!recentBookings.empty()) return recentBookings.back();
        return Ticket();
    }

    void removeLastBooking() {
        if (!recentBookings.empty())
            recentBookings.pop_back();
    }

    void showRecentBookings() const {
        if (recentBookings.empty()) {
            std::cout << "No recent bookings.\n";
            return;
        }
        std::cout << "Recent bookings for this event:\n";
        for (const auto& b : recentBookings) {
            std::cout << "Ticket ID: " << b.id
                << " | User: " << b.userName
                << " | Price: " << b.price << "\n";
        }
    }
};
