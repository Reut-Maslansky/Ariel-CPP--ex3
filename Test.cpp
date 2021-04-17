#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

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

TEST_CASE("build constructors")
{

    CHECK_NOTHROW(NumberWithUnits unit_km(3, "km"));
    CHECK_NOTHROW(NumberWithUnits unit_m(-6, "m"));
    CHECK_NOTHROW(NumberWithUnits unit_cm(5, "cm"));
    CHECK_NOTHROW(NumberWithUnits unit_g(1, "g"));
    CHECK_NOTHROW(NumberWithUnits unit_kg(23.7, "kg"));
    CHECK_NOTHROW(NumberWithUnits unit_ton(1, "ton"));
    CHECK_NOTHROW(NumberWithUnits unit_hour(4.7, "hour"));
    CHECK_NOTHROW(NumberWithUnits unit_min(30, "min"));
    CHECK_NOTHROW(NumberWithUnits unit_sec(-45, "sec"));
    CHECK_NOTHROW(NumberWithUnits unit_USD(-20, "USD"));
    CHECK_NOTHROW(NumberWithUnits unit_ILS(34, "ILS"));
}

TEST_CASE("Upper and Lower letters, and illigal types")
{

    CHECK_THROWS(NumberWithUnits(1, "Cm"));
    CHECK_THROWS(NumberWithUnits(2, "CM"));
    CHECK_THROWS(NumberWithUnits(3, "cM"));
    CHECK_THROWS(NumberWithUnits(4, "second"));
    CHECK_THROWS(NumberWithUnits(5, "kilogram"));
    CHECK_THROWS(NumberWithUnits(6, "Minutes"));
    CHECK_THROWS(NumberWithUnits(7, "aba"));
    CHECK_THROWS(NumberWithUnits(8, "day"));
    CHECK_THROWS(NumberWithUnits(9, "week"));
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

    CHECK_GT(unit_USD2, unit_ILS2);
    CHECK_GT(unit_min2, unit_hour2);
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

    CHECK_THROWS(unit_kg1.operator>=(unit_min1));
    CHECK_THROWS(unit_min1.operator>=(unit_kg1));
    CHECK_THROWS(unit_sec1.operator>=(unit_cm1));
    CHECK_THROWS(unit_cm1.operator>=(unit_sec1));

    CHECK_THROWS(unit_kg1.operator<(unit_sec1));
    CHECK_THROWS(unit_sec1.operator<(unit_m1));
    CHECK_THROWS(unit_g2.operator<(unit_USD1));
    CHECK_THROWS(unit_cm2.operator<(unit_g2));

    CHECK_THROWS(unit_kg1.operator>(unit_sec1));
    CHECK_THROWS(unit_m1.operator>(unit_sec1));
    CHECK_THROWS(unit_USD1.operator>(unit_g2));
    CHECK_THROWS(unit_cm2.operator>(unit_USD1));
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

    NumberWithUnits temp11{12, "min"};
    temp11 -= unit_min1;
    CHECK_EQ(temp11, NumberWithUnits{-18, "min"});
    NumberWithUnits temp22{108, "kg"};
    temp22 -= unit_kg1;
    CHECK_EQ(temp22, NumberWithUnits{3, "kg"});
    NumberWithUnits temp33{35, "m"};
    temp33 -= unit_m1;
    CHECK_EQ(temp33, NumberWithUnits{29, "m"});
    NumberWithUnits temp44{7, "hour"};
    temp44 -= unit_min1;
    CHECK_EQ(temp4, NumberWithUnits{-23, "hour"});
    NumberWithUnits temp55{45, "min"};
    temp55 -= unit_hour1;
    CHECK_EQ(temp55, NumberWithUnits{-3.25, "min"});
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

TEST_CASE("++ operation")
{

    //prefix
    CHECK_EQ(++unit_ton1, NumberWithUnits{2, "ton"});

    //postfix
    unit_ton1++;
    CHECK_EQ(unit_ton1, NumberWithUnits{3, "ton"});
    CHECK_EQ(unit_ton1++, NumberWithUnits{3, "ton"});
    CHECK_EQ(unit_ton1, NumberWithUnits{4, "ton"});
}

TEST_CASE("-- operation")
{

    //prefix
    CHECK_EQ(--unit_ton1, NumberWithUnits{3, "ton"});

    //postfix
    unit_ton1--;
    CHECK_EQ(unit_ton1, NumberWithUnits{2, "ton"});
    CHECK_EQ(unit_ton1--, NumberWithUnits{2, "ton"});
    CHECK_EQ(unit_ton1, NumberWithUnits{1, "ton"});
}

TEST_CASE("unary operation")
{
    CHECK_EQ(-unit_USD1, NumberWithUnits{-20, "USD"});
    CHECK_EQ(-unit_USD1, NumberWithUnits{20, "USD"});
    CHECK_EQ(-unit_g1, NumberWithUnits{-1, "USD"});
    CHECK_EQ(-unit_g1, NumberWithUnits{1, "USD"});

    CHECK_EQ(+unit_sec2, NumberWithUnits{80, "sec"});
    CHECK_EQ(+unit_kg2, NumberWithUnits{23.5, "kg"});
}

TEST_CASE("* operation")
{
    CHECK_EQ(3 * NumberWithUnits{-21, "ton"}, NumberWithUnits{-63, "ton"});
    CHECK_EQ(12.3 * NumberWithUnits{10, "cm"}, NumberWithUnits{123, "cm"});
    CHECK_EQ(2 * NumberWithUnits{-30, "sec"}, NumberWithUnits{-60, "sec"});

    CHECK_EQ(NumberWithUnits{20, "ILS"} * 7, NumberWithUnits{140, "ILS"});
    CHECK_EQ(NumberWithUnits{-17, "m"} * 2, NumberWithUnits{-34, "m"});
    CHECK_EQ(NumberWithUnits{-45, "min"} * 1, NumberWithUnits{-45, "min"});

    CHECK_EQ(5 * NumberWithUnits{-45, "kg"} * 2, NumberWithUnits{-450, "kg"});
    CHECK_EQ(3 * NumberWithUnits{2, "USD"} * 4, NumberWithUnits{24, "USD"});
    CHECK_EQ(-24 * NumberWithUnits{-1, "g"} * -2, NumberWithUnits{-48, "g"});
}

TEST_CASE("<< operation")
{
    ostringstream out;
    NumberWithUnits u1{7.789789, "km"};
    out << u1;
    CHECK_EQ(out.str(), "7.789789[km]");

    NumberWithUnits u2{-1, "USD"};
    ostringstream out1;
    out1 << u2;
    CHECK_EQ(out1.str(), "-1[USD]");

    NumberWithUnits u3{5, "g"};
    ostringstream out2;
    out2 << u3;
    CHECK_EQ(out2.str(), "5[g]");
}

TEST_CASE(">> operation")
{
    NumberWithUnits simple{6, "sec"};
    istringstream in("7 [ton] ");
    istringstream in1("8[g] ");
    istringstream in2("23[cm]");
    istringstream in3("-1[ kg]");
    istringstream in4("-9[m ]");

    in >> simple;
    CHECK_EQ(simple, NumberWithUnits{7, "ton"});
    in1 >> simple;
    CHECK_EQ(simple, NumberWithUnits{8, "g"});
    in2 >> simple;
    CHECK_EQ(simple, NumberWithUnits{23, "cm"});
    in3 >> simple;
    CHECK_EQ(simple, NumberWithUnits{-1, "kg"});
    in4 >> simple;
    CHECK_EQ(simple, NumberWithUnits{-9, "m"});
}

TEST_CASE("second read_units")
{
    // Open file
    ofstream SecFile("SecFile.txt");

    SecFile << "1 day = 24 hour" << endl;
    SecFile << "1 week = 7 day" << endl;

    // Close the file
    SecFile.close();

    ifstream units_file_Sec{"SecFile.txt"};
    CHECK_NOTHROW(NumberWithUnits::read_units(units_file_Sec));
}

TEST_CASE("constructors after another file")
{
    CHECK_NOTHROW(NumberWithUnits day1(7, "day")); //1 week, 168 hour
    CHECK_NOTHROW(NumberWithUnits day2(1, "day"));
    CHECK_NOTHROW(NumberWithUnits week1(1, "week"));   //7 day
    CHECK_NOTHROW(NumberWithUnits week2(0.5, "week")); //3.5 day

    //from the first file
    CHECK_NOTHROW(NumberWithUnits hour(48, "hour")); //2 day
}

NumberWithUnits day1(7, "day"); //1 week, 168 hour
NumberWithUnits day2(1, "day");
NumberWithUnits week1(1, "week");   //7 day
NumberWithUnits week2(0.5, "week"); //3.5 day

//from the first file
NumberWithUnits hour(48, "hour"); //2 day

TEST_CASE("operation after another file")
{
    CHECK(day1 == week1);
    CHECK(hour == NumberWithUnits (2, "day"));

    CHECK_NE(day2, week2);

    CHECK_LE(week2, day1);

    CHECK_GE(day1, week2);

    CHECK_LT(week2, day1);

    CHECK_GT(day1, week2);
    CHECK_GT(week2, hour);
}