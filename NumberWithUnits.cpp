#include "NumberWithUnits.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace ariel
{
    map<string, map<string, double>> NumberWithUnits::myUnits;
    void NumberWithUnits::read_units(ifstream &file)
    {
        if (file)
        {
            string u;
            while (getline(file, u))
            {
                string parent, operatorE, child;
                double one, number;
                istringstream(u) >> skipws >> one >> parent >> operatorE >> number >> child;
                if (!myUnits.count(parent))
                {
                    myUnits.insert({parent, map<string, double>{}});
                }
                if (!myUnits.count(child))
                {
                    myUnits.insert({child, map<string, double>{}});
                }

                for (auto elem : myUnits.at(parent))
                {
                    double tempAmount = elem.second * number;
                    string tempName = elem.first;
                    myUnits.at(tempName).insert({child, tempAmount});
                    myUnits.at(child).insert({tempName, 1 / tempAmount});
                }

                for (auto elem : myUnits.at(child))
                {
                    double tempAmount = elem.second * number;
                    string tempName = elem.first;
                    myUnits.at(tempName).insert({parent, 1 / tempAmount});
                    myUnits.at(parent).insert({tempName, tempAmount});
                }

                myUnits.at(parent).insert({child, number});
                myUnits.at(child).insert({parent, (1 / number)});
            }
        }
    }
    NumberWithUnits::NumberWithUnits(double a, std::string n)
    {
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

    // += / -= operation
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &u)
    {
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &u)
    {
        return *this;
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
        return os << (u.amount) << "[" << u.name << "]";
    }
    std::istream &operator>>(std::istream &is, NumberWithUnits &u)
    {
        return is;
    }
};