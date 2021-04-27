/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
      ofstream MyFile2("filename2.txt");

    // Write to the file
    MyFile2 << "1 r_school = 25 r_class\n1 r_class = 25 r_student\n1 r_EUR = 4 r_ILS\n1 r_halfMin = 0.5 r_min";
    MyFile2.close();

    ifstream units_MyFile2{"filename2.txt"};
    NumberWithUnits::read_units(units_MyFile2);
    NumberWithUnits temp_output(2, "r_class");
    NumberWithUnits temp_output1(3, "r_student");
    ostringstream oss;
    oss << temp_output << " " << temp_output1;
    cout << oss.str() << endl; //.compare("2[r_class] 3[r_student]")

    NumberWithUnits a(7, "r_EUR");
    NumberWithUnits b(7, "r_ILS");
    NumberWithUnits c(7, "r_ILS");
    istringstream iss{" 8 [   r_EUR     ]   -1 [r_school ] 29.7 [r_halfMin ]"};
    iss >> a >> b >> c;
    cout << (a == NumberWithUnits(8, "r_EUR")) << endl;
    cout << (b == NumberWithUnits(-1, "r_school")) << endl;

  return 0;
}
