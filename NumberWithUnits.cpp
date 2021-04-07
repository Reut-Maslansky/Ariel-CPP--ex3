#include "NumberWithUnits.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace ariel
{
    void NumberWithUnits::read_units(ifstream &file)
    {
        if (file)
        {
            // v.push_back(NodeU("", "", 0));
        }
    }

    NumberWithUnits::NumberWithUnits(double a, std::string n)
    {

        // for (unsigned int i = 0; i < v.size(); i++)
        // {
        //     if (v.at(i).nameFather == n)
        //     {
        //         amount = a;
        //         name = n;
        //         break;
        //     }
        //throw invalid_argument("invalid input");
        // }
        amount = a;
        name = n;
    }

    //Compare operation
    bool NumberWithUnits::operator==(const NumberWithUnits &u) const
    {
        return true;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &u) const
    {
        return true;
    }
    bool NumberWithUnits::operator>(const NumberWithUnits &u) const
    {
        return true;
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &u) const
    {
        return true;
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &u) const
    {
        return true;
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &u) const
    {
        return true;
    }

    bool NumberWithUnits::operator+=(const NumberWithUnits &u)
    {
        return true;
    }
    bool NumberWithUnits::operator-=(const NumberWithUnits &u)
    {
        return true;
    }

    // prefix  ++a
    NumberWithUnits &NumberWithUnits::operator++()
    {
        return *this;
    }
    // postfix a++
    const NumberWithUnits NumberWithUnits::operator++(int)
    {
        return NumberWithUnits(amount, name);
    }
    // prefix  --a
    NumberWithUnits &NumberWithUnits::operator--()
    {
        return *this;
    }
    // postfix a--
    const NumberWithUnits NumberWithUnits::operator--(int)
    {
        return NumberWithUnits(amount, name);
    }

    //Plus/Minus operation
    NumberWithUnits operator+(const NumberWithUnits &u1, const NumberWithUnits &u2)
    {
        ////throw expception
        return NumberWithUnits(1, "");
    }
    NumberWithUnits operator-(const NumberWithUnits &u1, const NumberWithUnits &u2)
    {
        ///////fix
        ////throw expception
        return NumberWithUnits(1, "");
    }

    //Mul operation
    NumberWithUnits operator*(const double d, const NumberWithUnits &u1)
    {
        return NumberWithUnits(1, "");
    }
    NumberWithUnits operator*(const NumberWithUnits &u1, const double d)
    {
        return NumberWithUnits(1, "");
    }

    //Unary operation
    NumberWithUnits operator+(const NumberWithUnits &u1)
    {
        return NumberWithUnits(1, "");
    }
    NumberWithUnits operator-(const NumberWithUnits &u1)
    {
        return NumberWithUnits(1, "");
    }

    //Input/Output operation
    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &u)
    {
        return os << u.amount << "[" << u.name << "]";
    }
    std::istream &operator>>(std::istream &is, NumberWithUnits &u)
    {
        return is;
    }

};