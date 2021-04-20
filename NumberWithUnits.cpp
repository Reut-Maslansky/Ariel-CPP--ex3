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
        else
        {
            throw string("no such file");
        }
    }

    NumberWithUnits::NumberWithUnits(double a, string n) : amount(a), name(n)
    {
        if (!myUnits.count(n))
        {
            throw invalid_argument("illigal type");
        }
    }

    bool sameType(string a, string b)
    {
        return NumberWithUnits::myUnits.at(a).count(b) && NumberWithUnits::myUnits.at(b).count(a);
    }

    //Compare operation
    bool NumberWithUnits::operator==(const NumberWithUnits &u) const
    {
        if (name == u.name)
        {
            return amount == u.amount;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }
        else
        {
            return myUnits.at(name).at(u.name) * amount == u.amount;
        }
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &u) const
    {
        return !this->operator==(u);
    }
    bool NumberWithUnits::operator>(const NumberWithUnits &u) const
    {
        if (name == u.name)
        {
            return amount > u.amount;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }
        else
        {
            return myUnits.at(name).at(u.name) * amount > u.amount;
        }
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &u) const
    {
        if (name == u.name)
        {
            return amount < u.amount;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }
        else
        {
            return myUnits.at(name).at(u.name) * amount < u.amount;
        }
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &u) const
    {
        return !this->operator<(u);
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &u) const
    {
        return !this->operator>(u);
    }

    // += / -= operation
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &u)
    {
        if (name == u.name)
        {
            amount += u.amount;
            return *this;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }
        else
        {
            amount += myUnits.at(u.name).at(name) * u.amount;
            return *this;
        }
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &u)
    {
        if (name == u.name)
        {
            amount -= u.amount;
            return *this;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }
        else
        {
            amount -= myUnits.at(u.name).at(name) * u.amount;
            return *this;
        }
    }

    // prefix  ++a
    NumberWithUnits &NumberWithUnits::operator++()
    {
        amount++;
        return *this;
    }
    // postfix a++
    const NumberWithUnits NumberWithUnits::operator++(int)
    {
        NumberWithUnits before(amount, name);
        amount++;
        return before;
    }
    // prefix  --a
    NumberWithUnits &NumberWithUnits::operator--()
    {
        amount--;
        return *this;
    }
    // postfix a--
    const NumberWithUnits NumberWithUnits::operator--(int)
    {
        NumberWithUnits before(amount, name);
        amount--;
        return before;
    }

    //Plus/Minus operation
    NumberWithUnits operator+(const NumberWithUnits &u1, const NumberWithUnits &u2)
    {
        if (u1.name == u2.name)
        {
            double tempAmount = u1.amount + u2.amount;
            return NumberWithUnits{tempAmount, u1.name};
        }
        if (!sameType(u1.name, u2.name))
        {
            throw invalid_argument("Not Same Type");
        }
        else
        {
            double tempAmount = u1.amount + NumberWithUnits::myUnits.at(u2.name).at(u1.name) * u2.amount;
            return NumberWithUnits{tempAmount, u1.name};
        }
    }

    NumberWithUnits operator-(const NumberWithUnits &u1, const NumberWithUnits &u2)
    {
        if (u1.name == u2.name)
        {
            double tempAmount = u1.amount - u2.amount;
            return NumberWithUnits{tempAmount, u1.name};
        }
        if (!sameType(u1.name, u2.name))
        {
            throw invalid_argument("Not Same Type");
        }
        else
        {
            double tempAmount = u1.amount - NumberWithUnits::myUnits.at(u2.name).at(u1.name) * u2.amount;
            return NumberWithUnits{tempAmount, u1.name};
        }
    }

    //Mul operation
    NumberWithUnits operator*(const double d, const NumberWithUnits &u1)
    {
        return NumberWithUnits(d * u1.amount, u1.name);
    }
    NumberWithUnits operator*(const NumberWithUnits &u1, const double d)
    {
        return NumberWithUnits(d * u1.amount, u1.name);
    }

    //Unary operation
    NumberWithUnits operator+(const NumberWithUnits &u1)
    {
        return NumberWithUnits(u1.amount, u1.name);
    }
    NumberWithUnits operator-(const NumberWithUnits &u1)
    {
        return NumberWithUnits(-u1.amount, u1.name);
    }

    //Input/Output operation
    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &u)
    {
        return os << (u.amount) << "[" << u.name << "]";
    }
    std::istream &operator>>(std::istream &is, NumberWithUnits &u)
    {
        char sign1, sign2;
        string tempName;
        double tempAmount;
        is >> skipws >> tempAmount >> sign1 >> tempName;
        if (tempName.at(tempName.length() - 1) != ']')
        {
            is >> sign2;
        }
        else
        {
            tempName = tempName.substr(0, tempName.length() - 1);
        }
        if (!NumberWithUnits::myUnits.count(tempName))
        {
            throw invalid_argument("illigal type");
        }
        u.amount = tempAmount;
        u.name = tempName;
        return is;
    }
};