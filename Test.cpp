#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <fstream>
#include <iostream>

using namespace ariel;
using namespace std;

TEST_CASE("read_units")
{
    // Open file
    ofstream File("File.txt");

    File << "1 km = 1000 m" << endl;
    File << "1 m = 100 cm" << endl;
    File << "1 kg = 1000 g" << endl;
    File << "1 ton = 1000 kg" << endl;
    File << "1 hour = 60 min" << endl;
    File << "1 min = 60 sec" << endl;
    File << "1 USD = 3.33 ILS ";

    // Close the file
    File.close();

    ifstream units_file{"File.txt"};
    CHECK_NOTHROW(NumberWithUnits::read_units(units_file));
}

NumberWithUnits unit_km1{3, "km"};
NumberWithUnits unit_km2{8.4, "km"}; //8400 m
NumberWithUnits unit_m1{6, "m"};
NumberWithUnits unit_m2{90.4, "m"}; //904 cm
NumberWithUnits unit_cm1{5, "cm"};
NumberWithUnits unit_cm2{110.8, "cm"}; //1.108 m
NumberWithUnits unit_g1{1, "g"};
NumberWithUnits unit_g2{4.8, "g"}; //0.0048 kg
NumberWithUnits unit_kg1{105, "kg"};
NumberWithUnits unit_kg2{23.5, "kg"}; //0.0235 t
NumberWithUnits unit_ton1{1, "ton"};
NumberWithUnits unit_ton2{23.6, "ton"}; //236000 kg
NumberWithUnits unit_hour1{4, "hour"};
NumberWithUnits unit_hour2{0.5, "hour"}; //30 min
NumberWithUnits unit_min1{30, "min"};
NumberWithUnits unit_min2{1.18, "min"}; //70.8 sec
NumberWithUnits unit_sec1{45, "sec"};
NumberWithUnits unit_sec2{80, "sec"}; //1.2 min
NumberWithUnits unit_USD1{20, "USD"};
NumberWithUnits unit_USD2{50.8, "USD"}; //169.164 ILS
NumberWithUnits unit_ILS1{34, "ILS"};
NumberWithUnits unit_ILS2{23.6763, "ILS"}; //7.11 USD

TEST_CASE("Compare operation same types")
{
    CHECK(unit_hour2 == unit_min1);
    CHECK(unit_min1 == unit_hour2);
    CHECK(unit_ton2 == NumberWithUnits{236000, "kg"});
    CHECK(NumberWithUnits{236000, "kg"} == unit_ton2);

    CHECK_NE(unit_ILS1, unit_USD1);
    CHECK_NE(unit_kg1, unit_kg1);

    CHECK_LE(unit_hour2, unit_min1);
    CHECK_LE(unit_hour2, unit_min2);
    CHECK_LE(unit_ILS2, unit_USD2);
    CHECK_LE(unit_ton1, unit_ton1);

    CHECK_GE(unit_hour2, unit_min1);
    CHECK_GE(unit_g2, unit_g2);
    CHECK_GE(unit_kg2, unit_g1);
    CHECK_GE(unit_ton2, unit_kg2);
    CHECK_GE(unit_sec2, unit_min2);

    CHECK_LT(unit_ILS2, unit_USD2);
    CHECK_LT(unit_hour2, unit_min2);

    CHECK_GT(2, 1);
    CHECK_GT(2, 1);
}

TEST_CASE("Compare operation diff types")
{
    CHECK_THROWS(unit_kg1.operator==(unit_min1));
    CHECK_THROWS(unit_min1.operator==(unit_kg1));
    CHECK_THROWS(unit_USD2.operator==(unit_km1));
    CHECK_THROWS(unit_km1.operator==(unit_USD2));

    CHECK_THROWS(unit_m2.operator!=(unit_ILS2));
    CHECK_THROWS(unit_ILS2.operator!=(unit_m2));
    CHECK_THROWS(unit_sec1.operator!=(unit_ton1));
    CHECK_THROWS(unit_ton1.operator!=(unit_sec1));

    CHECK_THROWS(unit_min1.operator<=(unit_kg1));
    CHECK_THROWS(unit_kg1.operator<=(unit_min1));
    CHECK_THROWS(unit_cm1.operator<=(unit_sec1));
    CHECK_THROWS(unit_sec1.operator<=(unit_cm1));

    //  CHECK_THROWS(.operator>=());
    //  CHECK_THROWS(.operator>=());
    //  CHECK_THROWS(.operator>=());
    //  CHECK_THROWS(.operator>=());

    //  CHECK_THROWS(.operator<());
    //  CHECK_THROWS(.operator<());
    //  CHECK_THROWS(.operator<());
    //  CHECK_THROWS(.operator<());

    //  CHECK_THROWS(.operator>());
    //  CHECK_THROWS(.operator>());
    //  CHECK_THROWS(.operator>());
    //  CHECK_THROWS(.operator>());
}

TEST_CASE("Plus/Minus operation same types")
{
    CHECK_EQ(unit_min1 + unit_min2, NumberWithUnits{31.18, "min"});
    CHECK_EQ(unit_kg1 + unit_kg2, NumberWithUnits{128.5, "kg"});
    CHECK_EQ(unit_m1 + unit_m2, NumberWithUnits{96.4, "m"});

    CHECK_EQ(unit_hour2 + unit_min2, NumberWithUnits{4.5, "hour"});
    CHECK_EQ(unit_min2 + unit_hour2, NumberWithUnits{270, "min"});

    NumberWithUnits temp1{12, "min"};
    temp1 += unit_min1;
    CHECK_EQ(temp1, NumberWithUnits{42, "min"});
    NumberWithUnits temp2{8, "kg"};
    temp2 += unit_kg1;
    CHECK_EQ(temp2, NumberWithUnits{113, "kg"});
    NumberWithUnits temp3{35, "m"};
    temp3 += unit_m1;
    CHECK_EQ(temp3, NumberWithUnits{41, "m"});
    NumberWithUnits temp4{7, "hour"};
    temp4 += unit_min1;
    CHECK_EQ(temp4, NumberWithUnits{7.5, "hour"});
    NumberWithUnits temp5{45, "min"};
    temp5 += unit_hour1;
    CHECK_EQ(temp5, NumberWithUnits{4.75, "min"});

    CHECK_EQ(unit_min1 - unit_min2, NumberWithUnits{28.82, "min"});
    CHECK_EQ(unit_kg1 - unit_kg2, NumberWithUnits{81.5, "kg"});
    CHECK_EQ(unit_m1 - unit_m2, NumberWithUnits{-84.4, "m"});

    CHECK_EQ(unit_hour2 - unit_min1, NumberWithUnits{0, "hour"});
    CHECK_EQ(unit_min1 - unit_hour2, NumberWithUnits{0, "min"});
    CHECK_EQ(unit_min2 - unit_hour2, NumberWithUnits{-28.82, "min"});

    NumberWithUnits temp1{12, "min"};
    temp1 -= unit_min1;
    CHECK_EQ(temp1, NumberWithUnits{-18, "min"});
    NumberWithUnits temp2{108, "kg"};
    temp2 -= unit_kg1;
    CHECK_EQ(temp2, NumberWithUnits{3, "kg"});
    NumberWithUnits temp3{35, "m"};
    temp3 -= unit_m1;
    CHECK_EQ(temp3, NumberWithUnits{29, "m"});
    NumberWithUnits temp4{7, "hour"};
    temp4 -= unit_min1;
    CHECK_EQ(temp4, NumberWithUnits{-23, "hour"});
    NumberWithUnits temp5{45, "min"};
    temp5 -= unit_hour1;
    CHECK_EQ(temp5, NumberWithUnits{-3.25, "min"});
}

TEST_CASE("Plus/Minus operation diff types")
{
    CHECK_THROWS(unit_hour2 + unit_USD1);
    CHECK_THROWS(unit_USD1 + unit_hour2);
    CHECK_THROWS(unit_cm1 + unit_ton2);

    CHECK_THROWS(unit_min1 += unit_kg2);
    CHECK_THROWS(unit_kg1 += unit_min2);
    CHECK_THROWS(unit_ILS1 += unit_cm1);
    CHECK_THROWS(unit_m1 += unit_USD2);

    CHECK_THROWS(unit_hour2 - unit_USD1);
    CHECK_THROWS(unit_USD1 - unit_hour2);
    CHECK_THROWS(unit_cm1 - unit_ton2);

    CHECK_THROWS(unit_min1 -= unit_kg2);
    CHECK_THROWS(unit_kg1 -= unit_min2);
    CHECK_THROWS(unit_ILS1 -= unit_cm1);
    CHECK_THROWS(unit_m1 -= unit_USD2);
}