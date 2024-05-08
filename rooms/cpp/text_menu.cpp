#include <iostream>
#include "../hpp/text_menu.hpp"
#include "../hpp/rooms_list.hpp"

void TextMenu::run() {
    while (true) {
        std::cout << "1. Add one room\n";
        std::cout << "2. Add two room\n";
        std::cout << "3. Add three room\n";
        std::cout << "4. Add four room\n";
        std::cout << "5. Display rooms\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter number of rooms to add: ";
                std::cin >> count;
                for (unsigned int i = 0; i < count; ++i) {
                    std::cout << "Enter room number for room " << i+1 << ": ";
                    std::cin >> number;
                    roomsList.add_one_room(number);
                }
                break;
            case 2:
                std::cout << "Enter number of rooms to add: ";
                std::cin >> count;
                for (unsigned int i = 0; i < count; ++i) {
                    std::cout << "Enter room number for room " << i+1 << ": ";
                    std::cin >> number;
                    roomsList.add_two_room(number);
                }
                break;
            case 3:
                std::cout << "Enter number of rooms to add: ";
                std::cin >> count;
                for (unsigned int i = 0; i < count; ++i) {
                    std::cout << "Enter room number for room " << i+1 << ": ";
                    std::cin >> number;
                    roomsList.add_three_room(number);
                }
                break;
            case 4:
                std::cout << "Enter number of rooms to add: ";
                std::cin >> count;
                for (unsigned int i = 0; i < count; ++i) {
                    std::cout << "Enter room number for room " << i+1 << ": ";
                    std::cin >> number;
                    roomsList.add_four_room(number);
                }
                break;
            case 5:
                roomsList.display();
                break;
            case 6:
                return;
            default:
                std::cout << "Invalid choice\n";
        }
    }
}