#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string>
#include <utility>
#include <list>
using namespace std;


namespace ariel{
    static map<pair<string,string>, double> values_map;
    static map<string, list<string>> chain_map;
    class Node{
        public:
            string unit;
            double value;
    };
    class NumberWithUnits{
        public:
            

            //Read units from file
            static ifstream& read_units(ifstream& file);
            static double covertUnits(string fromUnit, string toUnit,double value);
            static double covertUnitsChain(string fromUnit, string toUnit,double value);
            NumberWithUnits(double value, std::string type);
            NumberWithUnits(int value, std::string type);
            //For + operators
            const NumberWithUnits operator+(const NumberWithUnits& other) const;
            NumberWithUnits& operator+=(const NumberWithUnits& other);
            const NumberWithUnits operator+() const{
                return NumberWithUnits(this->value, this->type);
            }

            //For - operator
            const NumberWithUnits operator-(const NumberWithUnits& other) const;
            NumberWithUnits& operator-=(const NumberWithUnits& other);
            const NumberWithUnits operator-() const{
                return NumberWithUnits(this->value*(-1.0), this->type);
            }

            //For < operator 
            friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& other);
            friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& other);

            //For > operator
            friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& other);
            friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& other);

            friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& other);
            friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& other);


            NumberWithUnits& operator++() {
                value++;
                return *this;
            }

            // postfix increment:
            const NumberWithUnits operator++(int dummy_flag_for_postfix_increment) {
                NumberWithUnits copy = *this;
                value++;
                return copy;
            }

            NumberWithUnits& operator--() {
                value--;
                return *this;
            }

            // postfix increment:
            const NumberWithUnits operator--(int dummy_flag_for_postfix_increment) {
                NumberWithUnits copy = *this;
                value--;
                return copy;
            }


            friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& n);
            friend std::istream& operator>> (istream& input, NumberWithUnits& n) ;

            friend const NumberWithUnits operator*(const NumberWithUnits& n1, const double num);
            friend const NumberWithUnits operator*(const double num,const NumberWithUnits& n1);

            double value;
            string type;

            
        private:
            
    };
}