#pragma once
#include <string>

struct Ticket {
    int id;
    std::string userName;
    std::string eventName;
    std::string eventDate;
    // std::string eventID;
    double price;
    // bool status;

    Ticket() = default;
    Ticket(int i, const std::string& u, const std::string& e, const std::string& d, double p)
        : id(i), userName(u), eventName(e), eventDate(d), price(p) {}
};
