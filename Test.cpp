#include "doctest.h"
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Plus operators"){
    ifstream units_file{"units.txt"};
    ariel::NumberWithUnits::read_units(units_file);
    //Same units
    NumberWithUnits a {1, "km"};
    NumberWithUnits b {1, "km"};
    NumberWithUnits c = a + b;
    CHECK(c.operator==(NumberWithUnits{2,"km"}) == true); 
    
    //++ operator
    a++;
    CHECK(a.value == 2);

    //+= operator
    NumberWithUnits temp{2,"km"};
    temp+=a;
    CHECK(temp.value == 4);
    CHECK(temp.type == std::string("km"));
}

TEST_CASE("Minus operator"){
    ifstream units_file{"units.txt"};
    ariel::NumberWithUnits::read_units(units_file);
    //Same units
    NumberWithUnits a {1, "km"};
    NumberWithUnits b {1, "km"};
    NumberWithUnits c = a - b;
    CHECK(c.operator==(NumberWithUnits{0,"km"}) == true); 
    
    //-- operator
    a--;
    CHECK(a.value == 0);

    //+= operator
    NumberWithUnits temp{2,"km"};
    temp-=b;
    CHECK(temp.value == 1);
    CHECK(temp.type == std::string("km"));
}

TEST_CASE("Gt operator"){
    ifstream units_file{"units.txt"};
    ariel::NumberWithUnits::read_units(units_file);
    //Same units operator >
    NumberWithUnits a {10, "cm"};
    NumberWithUnits b {5, "cm"};
    CHECK(a.operator>(b) == true); 
    CHECK(b.operator>=(b) == true);
    //False check
    CHECK(a.operator>(b) == false);

    //Not same units 
    NumberWithUnits temp{8,"min"};
    CHECK_THROWS(a.operator>(temp));
}

TEST_CASE("Lt operator"){
    ifstream units_file{"units.txt"};
    ariel::NumberWithUnits::read_units(units_file);
    //Same units operator <
    NumberWithUnits a {10, "cm"};
    NumberWithUnits b {5, "cm"};
    CHECK(a.operator<(b) == true); 
    CHECK(b.operator<=(b) == true);
    //False check
    CHECK(a.operator<(b) == false);

    //Not same units 
    NumberWithUnits temp{8,"min"};
    CHECK_THROWS(a.operator<(temp));
}

TEST_CASE("Equals/Not-equals")
{
    ifstream units_file{"units.txt"};
    ariel::NumberWithUnits::read_units(units_file);

    //Same units
    NumberWithUnits a {1, "cm"};
    NumberWithUnits b {1, "cm"};   

    CHECK(a.operator==(b) == true);

    //Diffrent units
    NumberWithUnits a1 {1, "cm"};
    NumberWithUnits b1 {0.01, "m"};

    CHECK(a1.operator==(b1) == true);

    //-----Not Equals-----

        //Same units
    NumberWithUnits a2 {1, "cm"};
    NumberWithUnits b2 {0.1, "cm"};   

    CHECK(a2.operator!=(b2) == true);

    //Diffrent units
    NumberWithUnits a3 {1, "cm"};
    NumberWithUnits b3 {1, "min"};

    CHECK(a3.operator!=(b3) == true);
}

TEST_CASE("Multiply by an double")
{
    ifstream units_file{"units.txt"};
    ariel::NumberWithUnits::read_units(units_file);

    NumberWithUnits a {10, "cm"};
    //Double left
    a = a*3;
    CHECK(a.value == 30);
    //Double right
    a = 3*a;
    CHECK(a.value == 90);   
}


TEST_CASE("Bad units")
{
    ifstream units_file{"units.txt"};
    ariel::NumberWithUnits::read_units(units_file);
    //Empty type
    NumberWithUnits no_type {10, ""};
    CHECK_THROWS(no_type.operator+(no_type));
    //Bad type
    NumberWithUnits bad_type {10, "a"};
    CHECK_THROWS(bad_type.operator+(bad_type));
    //Diffrent types
    NumberWithUnits cm_type {10, "cm"};
    NumberWithUnits hour_type {10, "hour"};
    CHECK_THROWS(cm_type.operator+(hour_type));

}