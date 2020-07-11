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
string numtoLengthunit(int input, bool & toEnd);
double lengthConversion(int unitbefore, int unitafter, double toconvert);

//Currency - USD, CAD, KRW, etc. Should reflect updated price
void currencyCalc();

//Area - acre, square feet, square meter, etc.
void areaCalc();
string numtoAreaunit(int input, bool & toEnd);
double areaConversion(int unitbefore, int unitafter, double toconvert);

//Temperature - Kelvin, Celsius, Fahrenheit
void temperatureCalc();
string numtoTemperatureunit(int input, bool & toEnd);
double temperatureConversion(int unitbefore, int unitafter, double toconvert);

//Data - bit, byte, ...
void dataCalc();
string numtoDataunit(int input, bool & toEnd);
double dataConversion(int unitbefore, int unitafter, double toconvert);

//Speed - meter per second, inch per second, km/h, etc.
void speedCalc();
string numtoSpeedunit(int input, bool & toEnd);
double speedConversion(int unitbefore, int unitafter, double toconvert);

//Time - milisecond, second, ..., week, etc.
void timeCalc();
string numtoTimeunit(int input, bool & toEnd);
double timeConversion(int unitbefore, int unitafter, double toconvert);

//Volume
void volumeCalc();
string numtoVolumeunit(int input, bool & toEnd);
double volumeConversion(int unitbefore, int unitafter, double toconvert);

#endif