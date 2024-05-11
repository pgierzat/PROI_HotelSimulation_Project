#include <iostream>

#ifndef AMOUNT_HPP
#define AMOUNT_HPP

class Amount {
        struct dollar_cent
        {
            int dollars;
            int cents;
            dollar_cent operator-() const;
        };
    public:
        Amount(int dollars, int cents);
        Amount() = default;
        int get_dollars() const;
        int get_cents() const;
        void set_amount(int dollars, int cents);
        bool operator==(const Amount& other) const;
        Amount& operator+=(const Amount&);
        Amount& operator-=(const Amount&);
        Amount& operator*=(int);
    private:
        void normalise_self();
        static dollar_cent normalise(int dollars, int cents);
        static dollar_cent normalise_positive(int cents);
        int dollars = 0;
        int cents = 0;
};


Amount operator-(const Amount&);

Amount operator+(Amount lhs, const Amount& rhs);

Amount operator-(Amount lhs, const Amount& rhs);

Amount operator*(Amount, int rhs);

std::ostream& operator<<(std::ostream&, const Amount&);

std::istream& operator>>(std::istream&, Amount&);

#endif
