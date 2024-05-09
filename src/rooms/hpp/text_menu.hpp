#include <iostream>
#include "../hpp/rooms_list.hpp"

class TextMenu {
    private:
        RoomsList roomsList;
        int choice;
        unsigned int number, count;
    public:
        void run();
};