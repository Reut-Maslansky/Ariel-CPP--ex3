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

NumberWithUnits unit_km1{3,"km"}; 
NumberWithUnits unit_km2{8.4,"km"}; //8400 m
NumberWithUnits unit_m1{6,"m"};
NumberWithUnits unit_m2{90.4,"m"}; //904 cm
NumberWithUnits unit_cm1{5,"cm"};
NumberWithUnits unit_cm2{110.8,"cm"}; //1.108 m
NumberWithUnits unit_cm2{1,"g"};
NumberWithUnits unit_cm2{4.8,"g"}; //0.0048 kg
NumberWithUnits unit_kg1{105,"kg"};
NumberWithUnits unit_kg2{23.5,"kg"}; //0.0235 t
NumberWithUnits unit_ton1{1,"ton"};
NumberWithUnits unit_ton2{23.6,"ton"}; //236000 kg
NumberWithUnits unit_hour1{4,"hour"};
NumberWithUnits unit_hour2{0.5,"hour"}; //30 min
NumberWithUnits unit_min1{30,"min"};
NumberWithUnits unit_min2{39.8,"min"}; //2388 sec
NumberWithUnits unit_min2{45,"sec"};
NumberWithUnits unit_min2{80.8,"sec"}; //1.28 min
NumberWithUnits unit_USD1{20,"USD"};
NumberWithUnits unit_USD2{50.8,"USD"}; //169.164 ILS
NumberWithUnits unit_ILS2{34,"ILS"};
NumberWithUnits unit_ILS2{23.6763,"ILS"}; //7.11 USD

TEST_CASE("Compare operation")
{
    
}