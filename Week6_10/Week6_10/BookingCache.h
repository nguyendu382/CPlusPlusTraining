#pragma once
#include <deque>

class BookingCache {
    std::deque<int> recentBookings;
    size_t maxSize;

public:
	BookingCache(size_t size = 10) : maxSize(size) {}

    void addBooking(int bookingId) {
        if (recentBookings.size() >= maxSize) {
			recentBookings.pop_front();
		}
        recentBookings.push_back(bookingId);
    }

    void removeLastBooking() {
        if (!recentBookings.empty()) {
            recentBookings.pop_back();
        }
    }

    const std::deque<int>& getRecentBookings() const {
        return recentBookings;
    }
};