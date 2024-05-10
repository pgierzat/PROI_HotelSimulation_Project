#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>

class Room {

    protected:
        unsigned number;
        unsigned capacity;
        unsigned base_price;

    public:
        Room(unsigned number, unsigned capacity);
        virtual unsigned calculatePersonel() const;
        virtual unsigned calculatePrice() const;
        virtual void display(std::ostream& os) const;
        unsigned getNumber() const;
        unsigned getCapacity() const;
        virtual bool operator==(const Room&) const = default;
        friend std::ostream& operator<<(std::ostream& os, const Room& room);
};


#endif