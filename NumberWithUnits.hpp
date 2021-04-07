#pragma once
#include <fstream>
#include <string>
#include <vector>

namespace ariel
{
    class NumberWithUnits
    {
        struct NoedU
        {
            std::string nameFather;
            std::string nameChild;
            int compare;

            NoedU(std::string father, std::string child, int com)
                : nameFather(father), nameChild(child), compare(com)
            {
            }
        };

        std::vector<NoedU> v;

    public:
        NumberWithUnits(int, std::string);
        void read_units(ifstream);

        //Compare operation
        bool operator==(const NumberWithUnits &u) const;
        bool operator!=(const NumberWithUnits &u) const;
        bool operator>(const NumberWithUnits &u) const;
        bool operator>=(const NumberWithUnits &u) const;
        bool operator<(const NumberWithUnits &u) const;
        bool operator<=(const NumberWithUnits &u) const;

        bool operator+=(const NumberWithUnits &u);
        bool operator-=(const NumberWithUnits &u);

        NumberWithUnits &operator++();         // prefix  ++a
        const NumberWithUnits operator++(int); // postfix a++
        NumberWithUnits &operator--();         // prefix  --a
        const NumberWithUnits operator--(int); // postfix a--

        //Plus/Minus operation
        friend NumberWithUnits operator+(const NumberWithUnits &u1, const NumberWithUnits &u2);
        friend NumberWithUnits operator-(const NumberWithUnits &u1, const NumberWithUnits &u2);

        //Mul operation
        friend NumberWithUnits operator*(const double d, const NumberWithUnits &u2);

        //Unary operation
        friend NumberWithUnits operator+(const NumberWithUnits &u1);
        friend NumberWithUnits operator-(const NumberWithUnits &u1);

        //Input/Output operation
        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &u);
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &u);
    };

}