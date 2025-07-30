#pragma once
#include <deque>
#include <iostream>
#include "Ticket.h"

class BookingCache {
    std::deque<Ticket> recentBookings;
    size_t maxSize;

public:
    BookingCache(size_t size = 10) : maxSize(size) {}

    void addBooking(const Ticket& b) {
        if (recentBookings.size() >= maxSize)
            recentBookings.pop_front();
        recentBookings.push_back(b);
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

        for (const auto& b : recentBookings) {
            std::cout << "Ticket ID: " << b.getId()
                << " | User: " << b.getUserName()
                << " | Event ID: " << b.getEventId()
                << " | Price: " << b.getPrice() << "\n";
        }
    }
};
