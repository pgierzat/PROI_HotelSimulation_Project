#include "amount.hpp"
#include <iostream>
#include <stdexcept>

Amount::dollar_cent Amount::dollar_cent::operator-() const
{
    Amount::dollar_cent out;
    out.dollars = -dollars;
    out.cents = -cents;
    return out;
}

Amount::Amount(int dollars, int cents) : dollars{dollars}, cents{cents}
{
    if (cents > 99 || cents < -99)
        throw std::invalid_argument("cents must be less than 100");
    dollar_cent dc = normalise(dollars, cents);
    this -> dollars = dc.dollars;
    this -> cents = dc.cents;
}

int Amount::get_dollars() const { return dollars; }

int Amount::get_cents() const { return cents; }

void Amount::set_amount(int dollars, int cents)
{
    if (cents > 99 || cents < -99)
        throw std::invalid_argument("cents must be less than 100");
    this -> dollars = dollars;
    this -> cents = cents;
    normalise_self();
}

bool Amount::operator==(const Amount& other) const
{
    return dollars == other.get_dollars() && cents == other.get_cents();
}

Amount& Amount::operator+=(const Amount& rhs)
{
    dollars += rhs.dollars;
    cents += rhs.cents;
    normalise_self();
    return *this;
}

Amount& Amount::operator-=(const Amount& rhs)
{
    dollars -= rhs.dollars;
    cents -= rhs.cents;
    normalise_self();
    return *this;
}

Amount& Amount::operator*=(int rhs)
{
    dollars *= rhs;
    cents *= rhs;
    normalise_self();
    return *this;
}

void Amount::normalise_self()
{
    dollar_cent x = normalise(dollars, cents);
    dollars = x.dollars;
    cents = x.cents;
}

Amount::dollar_cent Amount::normalise(int dollars, int cents)
{
    cents += 100 * dollars;
    if (cents >= 0)
        return normalise_positive(cents);
    else
        return -normalise_positive(-cents);
}

Amount::dollar_cent Amount::normalise_positive(int cents)
{
    dollar_cent x;
    x.dollars = cents / 100;
    cents -= x.dollars * 100;
    x.cents = cents;
    return x;
}

Amount operator-(const Amount& amount)
{
    return Amount{ -amount.get_dollars(), -amount.get_cents() };
}

Amount operator+(Amount lhs, const Amount& rhs)
{
    return lhs += rhs;
}

Amount operator*(Amount amount, int rhs)
{
    amount *= rhs;
    return amount;
}

std::ostream& operator<<(std::ostream& os, const Amount& amount)
{
    os << amount.get_dollars() << "." << amount.get_cents() << "$";
    return os;
}

std::istream& operator>>(std::istream& is, Amount& amount)
{
    int dollars;
    int cents;
    is >> dollars >> cents;
    amount.set_amount(dollars, cents);
    return is;
}
