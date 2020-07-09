#ifndef conversion_h
#define conversion_h

//conversion of units

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

//Conversion calculator
void conversionCalc();

//Mass - pound, kilogram, etc.
void massCalc();
string numtoMassunit(int input, bool & toEnd);
double massConversion(int unitbefore, int unitafter, double toconvert);

//Length - metre, feet, mile, etc.
void lengthCalc();

//Currency - USD, CAD, KRW, etc. Should reflect updated price
void currencyCalc();

//Area - acre, square feet, square meter, etc.
void areaCalc();

//Temperature - Kelvin, Celsius, Fahrenheit
void temperatureCalc();

//Data - bit, byte, ...
void dataCalc();

//Speed - meter per second, inch per second, km/h, etc.
void speedCalc();

//Time - milisecond, second, ..., week, etc.
void timeCalc();

#endif