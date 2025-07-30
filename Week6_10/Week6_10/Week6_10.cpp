#include <iostream>
#include "BookingSystem.h"

void showMainMenu() {
    std::cout << "\n======= SMART BOOKING SYSTEM =======\n";
    std::cout << "Welcome to the Smart Booking System!\n";
    std::cout << "Please choose an option:\n";
    std::cout << "------------------------------------\n";
    std::cout << "1. I am a User\n";
    std::cout << "2. I am an Event Manager\n";
    std::cout << "0. Exit\n";
    std::cout << "------------------------------------\n";
    std::cout << "Choice: ";
}

void showUserMenu() {

    std::cout << "\n--- User ---\n";
    std::cout << "1. View list of events\n";
    std::cout << "2. Book a ticket\n";
    std::cout << "3. Cancel a ticket\n";
    std::cout << "4. View booked tickets\n";
    std::cout << "5. Undo last booking\n";
    std::cout << "0. Back\n";
    std::cout << "Choice: ";
}

void showManagerMenu() {
    std::cout << "\n--- Manager ---\n";
    std::cout << "1. Add an event\n";
    std::cout << "2. Update event info\n";
    std::cout << "3. Remove an event\n";
    std::cout << "4. View list of events\n";
    std::cout << "5. Activate an event\n";
    std::cout << "6. View tickets of an event\n";
    std::cout << "7. View recent bookings\n";
    std::cout << "8. Undo last booking\n";
    std::cout << "0. Back\n";
    std::cout << "Choice: ";
}

void choiceUserMenu(BookingSystem& system) {
    std::string currentUser, name;
    std::cout << "Enter your username: ";
    std::cin >> currentUser;
    if (!system.userExists(currentUser)) {
        std::cout << "New user detected. Please enter your name: ";
        std::cin >> name;
        system.createUser(currentUser, name);
    }
    else {
        name = currentUser;
    }
    std::cout << "\nWelcome " << currentUser << "!\n";
    while (true) {
        int userChoice;
        showUserMenu();
        std::cin >> userChoice;
        switch (userChoice) {
        case 1:
            system.showEvents();
            break;
        case 2: {
            int eid; double price;
            std::cout << "Enter event ID: "; std::cin >> eid;
            std::cout << "Enter ticket price: "; std::cin >> price;
            system.bookTicket(currentUser, eid, price);
            break;
        }
        case 3: {
            int tid;
            std::cout << "Enter ticket ID: "; std::cin >> tid;
            system.cancelTicket(currentUser, tid);
            break;
        }
        case 4:
            system.showUserTickets(currentUser);
            break;
        case 5:
            system.undoLastBooking(currentUser);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice.\n";
        }
    }
}

void choiceManagerMenu(BookingSystem& system) {
    while (true) {
        int managerChoice;
        showManagerMenu();
        std::cin >> managerChoice;
        switch (managerChoice) {
        case 1: {
            int eid; std::string name, date, loc;
            std::cout << "Enter ID, name, date, location: ";
            std::cin >> eid >> name >> date >> loc;
            system.addEvent(eid, name, date, loc);
            break;
        }
        case 2: {
            int eid;
            std::cout << "Enter event ID to update: ";
            std::cin >> eid;
            system.updateEvent(eid);
            break;
        }
        case 3: {
            int eid;
            std::cout << "Enter event ID to remove: ";
            std::cin >> eid;
            system.removeEvent(eid);
            break;
        }
        case 4:
            system.showEvents();
            break;
        case 5: {
            int eid;
            std::cout << "Enter event ID to activate: ";
            std::cin >> eid;
            system.activateEvent(eid);
            break;
        }
        case 6: {
            int eid;
            std::cout << "Enter event ID to view tickets: ";
            std::cin >> eid;
            system.showTicketsForEvent(eid);
            break;
        }
        case 7: {
            int eid;
            std::cout << "Enter event ID to show recent bookings: ";
            std::cin >> eid;
            system.showRecentBookingsForEvent(eid);
            break;
        }
        case 8: {
            int eid;
            std::cout << "Enter event ID to undo last booking: ";
            std::cin >> eid;
            system.undoLastEventBooking(eid);
            break;
        }
        case 0:
            return;
        default:
            std::cout << "Invalid choice.\n";
        }
    }
}

void choiceMainMenu(BookingSystem& system) {
    while (true) {
        int choice;
        showMainMenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            choiceUserMenu(system);
            break;
        case 2:
            choiceManagerMenu(system);
            break;
        case 0:
            std::cout << "Good bye!\n";
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    BookingSystem system;
    system.loadFromJson("data.json");
    choiceMainMenu(system);
    system.saveToJson("data.json");
    return 0;
}

