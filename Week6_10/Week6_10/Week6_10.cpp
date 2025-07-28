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
    std::cout << "2. Remove an event\n";
    std::cout << "3. View list of events\n";
    std::cout << "4. View tickets of an event\n";
    std::cout << "5. View recent bookings\n";
    std::cout << "6. Undo last booking\n";
    std::cout << "0. Back\n";
    std::cout << "Choice: ";
}


int main() {
    BookingSystem system;
    std::string currentUser, email;
    int choice;

    while (true) {
        showMainMenu();
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter your username: ";
            std::cin >> currentUser;
            if (system.userExists(currentUser) == false) {
                std::cout << "Enter your email: ";
                std::cin >> email;
                system.createUser(currentUser, email);
            }

            int userChoice;
            do {
                showUserMenu();
                std::cin >> userChoice;
                switch (userChoice) {
                case 1:
                    system.showEvents(); break;
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
                    system.showUserTickets(currentUser); break;
                case 5:
                    system.undoLastBooking(currentUser); break;
                case 0:
                    break;
                default:
                    std::cout << "Invalid choice.\n";
                }
            } while (userChoice != 0);

        }
        else if (choice == 2) {
            int managerChoice;
            do {
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
                    std::cout << "Enter event ID to remove: ";
                    std::cin >> eid;
                    system.removeEvent(eid);
                    break;
                }
                case 3:
                    system.showEvents(); break;
                case 4: {
                    int eid;
                    std::cout << "Enter event ID to view tickets: ";
                    std::cin >> eid;
                    system.showTicketsForEvent(eid);
                    break;
                }
                case 5: {
                    int eid;
                    std::cout << "Enter event ID to show recent bookings: ";
                    std::cin >> eid;
                    system.showRecentBookingsForEvent(eid);
                    break;
                }

                case 6: {
                    int eid;
                    std::cout << "Enter event ID to undo last booking: ";
                    std::cin >> eid;
                    system.undoLastEventBooking(eid);
                    break;
                }
                case 0:
                    break;
                default:
                    std::cout << "Invalid choice.\n";
                }
            } while (managerChoice != 0);

        }
        else if (choice == 0) {
            std::cout << "Good bye!\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
    