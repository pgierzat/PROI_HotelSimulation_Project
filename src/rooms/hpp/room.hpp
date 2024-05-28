#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include "../../types/amount.hpp"

class Room {

    protected:
        unsigned number;
        unsigned capacity;
        static const Amount base_price;

    public:
        Room(unsigned number, unsigned capacity);
        virtual ~Room() = default;
        virtual unsigned calculatePersonel() const;
        virtual Amount calculatePrice() const;
        virtual void display(std::ostream& os) const;
        unsigned getNumber() const;
        unsigned getCapacity() const;
        virtual bool operator==(const Room&) const = default;
        friend std::ostream& operator<<(std::ostream& os, const Room& room);
};


#endif