#define _USE_MATH_DEFINES
#include "conversion.h"
using namespace std;

//mass conversion parameters
const double tonStdtoKg = 1000; //1ton = 1000kg
const double kgtoGram = 1000; //1kg = 1000g
const double gramtomg = 1000; //1g = 1000mg
const double tonUStoLb = 2000; //1 US ton = 2000lb
const double lbtoOz = 16; // 1lb = 16oz
const double tonUKtoLb = 2240; //1 UK ton = 2240lb
const double lbtoGram = 453.59237; // 1lb = 453.59237g

//length conversion parameters
const double kmtom = 1000; //1km =1000m
const double mtocm = 100; //1m = 100cm
const double cmtomm = 10; //1cm = 10mm
const double fttoin = 12; //1ft = 12in
const double ydtoft = 3; // 1yd = 3ft
const double miletoyd = 1760; // 1 mile = 1760 yd
const double nauticaltometer = 1852; //1 nm = 1852m
const double intomil = 1000; // 1 in = 1000 mils;
const double intocm = 2.54; //1in = 2.54cm

//currency conversion parameters

//area conversion parameters
const double acretosqft = 43560; //1 acre = 43560 ft^2
const double hectaretoare = 100; //1 hectare = 100 are
const double hectaretosqm = 10000; //1 hectare = 10000 m^2
const double sqkmtosqm = 1000000; // 1 km^2 = 1000000 m^2
const double sqmtosqcm = 10000; // 1m^2 = 10000cm^2
const double sqcmtosqmm = 100; // 1cm^2 = 100mm^2
const double sqmiletosqyd = 3097600; //1 mile^2 = 3097600 yd^2
const double sqydtosqft = 9; //1 yd^2 = 9 ft^2
const double sqfttosqin = 144; //1 ft^2 = 144in^2
const double sqintosqcm = 6.4516; //1 in^2 = 6.4516 cm^2

//data conversion parameters
const double bytetobit = 8;
const double kbtobyte = 1024;

//speed conversion paramenters

//time conversion parameters
const double stoms = 1000;
const double dtoh = 24;
const double wktod = 7;
const double yrtod = 365; //not always though...
//volume conversion parameters

//Conversion calculator
void conversionCalc(){
    int command;
    bool toEnd = false;
    while (!toEnd){
        cout << "Conversion Calculator" <<endl;
        cout << "1. Mass" << endl;
        cout << "2. Length" << endl;
        cout << "3. Currency" << endl;
        cout << "4. Area" << endl;
        cout << "5. Temperature" << endl;
        cout << "6. Data" << endl;
        cout << "7. Speed" << endl;
        cout << "8. Time" << endl;
        cout << "9. Volume" <<endl;
        cout << "0. Exit" << endl;
        cout << endl;
        cout << "Type feature to execute: ";
        cin >> command;
        switch(command){
            case 0:
                toEnd = true;
                cout << "Return back to main menu..."<<endl;
                break;
            case 1: massCalc(); break;
            case 2: lengthCalc(); break;
            case 3: currencyCalc(); break;
            case 4: areaCalc(); break;
            case 5: temperatureCalc(); break;
            case 6: dataCalc(); break;
            case 7: speedCalc(); break;
            case 8: timeCalc(); break;
            case 9: volumeCalc(); break;
            default: cout << "Error! Wrong input to execute. Try again..." <<endl; break;
        }
        cout << endl;
    }
}

// mass conversion

void massCalc(){
    cout << "Mass conversion calculator" <<endl;
    
    int beforeChange, afterChange;
    double toConvert, afterConvert;
    string unitBeforeChange, unitAfterChange;
    string statement;
    bool toEnd = false;
    while (!toEnd){
        cout << "Type corresponding number to make your choice" <<endl;
        cout << "1. ton (standard)" << endl;
        cout << "2. ton (US)" << endl;
        cout << "3. ton (UK)" << endl;
        cout << "4. lb (pound)" << endl;
        cout << "5. oz (ounce)" << endl;
        cout << "6. kg (kilogram)" << endl;
        cout << "7. g (gram)" <<endl;
        cout << "8. mg (milligram)" <<endl;
        cout << "0. exit" <<endl;

        cout << "Which unit do you want to convert from?" << endl;
        cin >> beforeChange;
        unitBeforeChange = numtoMassunit(beforeChange, toEnd);
        if(toEnd) break;
        
        cout << "What is the value to convert in " << unitBeforeChange << endl;
        cin >> toConvert;

        cout << "Which unit do you want to convert to?" << endl;
        cin >> afterChange;
        unitAfterChange = numtoMassunit(afterChange, toEnd);
        if(toEnd) break;

        afterConvert = massConversion(beforeChange,afterChange,toConvert);
        if (afterConvert<0){
            toEnd = true; 
            break;
        }   
        //Enable this if there is a plan to save history with filestream
        //statement = to_string(toConvert) + " " + unitBeforeChange +" is converted into " + to_string(afterConvert) + " " + unitAfterChange;
        cout << setprecision(2) << toConvert << " " << unitBeforeChange << " is converted into " << setprecision(2) << afterConvert << " " << unitAfterChange <<endl;
    }
    cout << "Returning back to selection menu..." <<endl;
}

string numtoMassunit(int input, bool & toEnd){
    string output;
    switch (input)
    {
    case 0:
        output = "";
        toEnd = true;
        break;
    case 1: output = "ton (standard)"; break;
    case 2: output = "ton (US)"; break;
    case 3: output = "ton (UK)"; break;
    case 4: output = "lb (pound)"; break;
    case 5: output = "oz (ounce)"; break;
    case 6: output = "kg (kilogram)"; break;
    case 7: output = "g (gram)"; break;
    case 8: output = "mg (milligram)"; break;
    default:
        cout << "Invalid input!" <<endl;
        output = "";
        break;
    }
    return output;

}

double massConversion(int unitbefore, int unitafter, double toconvert){
    double output;
    if (unitbefore == unitafter){
        //when unit before = unit after
        output = toconvert;
    }
    else if (unitbefore == 1 && unitafter == 2){
        //standard ton -> US ton
        output = toconvert*(tonStdtoKg*kgtoGram/lbtoGram)/tonUStoLb; 
    }
    else if (unitbefore == 1 && unitafter == 3){
        //standard ton -> UK ton
        output = toconvert*(tonStdtoKg*kgtoGram/lbtoGram)/tonUKtoLb; 
    }
    else if (unitbefore == 1 && unitafter == 4){
        //standard ton -> pound
        output = toconvert*(tonStdtoKg*kgtoGram/lbtoGram);
    }
    else if (unitbefore == 1 && unitafter == 5){
        //standard ton -> ounce
        output = toconvert*(tonStdtoKg*kgtoGram/lbtoGram)*lbtoOz; 
    }
    else if (unitbefore == 1 && unitafter == 6){
        //standard ton -> kilogram
        output = toconvert*tonStdtoKg; 
    }
    else if (unitbefore == 1 && unitafter == 7){
        //standard ton -> gram
        output = toconvert*tonStdtoKg*kgtoGram; 
    }
    else if (unitbefore == 1 && unitafter == 8){
        //standard ton -> milligram
        output = toconvert*tonStdtoKg*kgtoGram*gramtomg; 
    }
    else if (unitbefore == 2 && unitafter == 1){
        //US ton -> standard ton
        output = toconvert * (tonUStoLb*lbtoGram/kgtoGram)/tonStdtoKg; 
    }
    else if (unitbefore == 2 && unitafter == 3){
        //US ton -> UK ton
        output = toconvert * (tonUStoLb/tonUKtoLb); 
    }
    else if (unitbefore == 2 && unitafter == 4){
        //US ton -> pound
        output = toconvert * tonUStoLb; 
    }
    else if (unitbefore == 2 && unitafter == 5){
        //US ton -> ounce
        output = toconvert * tonUStoLb * lbtoOz; 
    }
    else if (unitbefore == 2 && unitafter == 6){
        //US ton -> kilogram
        output = toconvert * (tonUStoLb*lbtoGram/kgtoGram); 
    }
    else if (unitbefore == 2 && unitafter == 7){
        //US ton -> gram
        output = toconvert * (tonUStoLb*lbtoGram); 
    }
    else if (unitbefore == 2 && unitafter == 8){
        //US ton -> milligram
        output = toconvert * (tonUStoLb*lbtoGram*gramtomg); 
    }
    else if (unitbefore == 3 && unitafter == 1){
        //UK ton -> standard ton
        output = toconvert * (tonUKtoLb*lbtoGram/kgtoGram)/tonStdtoKg; 
    }
    else if (unitbefore == 3 && unitafter == 2){
        //UK ton -> US ton
        output = toconvert * (tonUKtoLb/tonUStoLb); 
    }
    else if (unitbefore == 3 && unitafter == 4){
        //UK ton -> pound
        output = toconvert * tonUKtoLb;
    }
    else if (unitbefore == 3 && unitafter == 5){
        //UK ton -> ounce
        output = toconvert * tonUKtoLb * lbtoOz;
    }
    else if (unitbefore == 3 && unitafter == 6){
        //UK ton -> kilogram
        output = toconvert * (tonUKtoLb*lbtoGram/kgtoGram);
    }
    else if (unitbefore == 3 && unitafter == 7){
        //UK ton -> gram
        output = toconvert * (tonUKtoLb*lbtoGram);
    }
    else if (unitbefore == 3 && unitafter == 8){
        //UK ton -> milligram
        output = toconvert * (tonUKtoLb*lbtoGram*gramtomg);
    }
     else if (unitbefore == 4 && unitafter == 1){
        //pound -> standard ton
        output = toconvert * (lbtoGram/kgtoGram)/tonStdtoKg; 
    }
    else if (unitbefore == 4 && unitafter == 2){
        //pound -> US ton
        output = toconvert / tonUStoLb; 
    }
    else if (unitbefore == 4 && unitafter == 3){
        //pound -> UK ton
        output = toconvert / tonUKtoLb; 
    }
    else if (unitbefore == 4 && unitafter == 5){
        //pound -> ounce
        output = toconvert * lbtoOz; 
    }
    else if (unitbefore == 4 && unitafter == 6){
        //pound -> kilogram
        output = toconvert * (lbtoGram/kgtoGram); 
    }
    else if (unitbefore == 4 && unitafter == 7){
        //pound -> gram
        output = toconvert * lbtoGram; 
    }
    else if (unitbefore == 4 && unitafter == 8){
        //pound -> milligram
        output = toconvert * (lbtoGram * gramtomg); 
    }
    else if (unitbefore == 5 && unitafter == 1){
        //ounce -> standard ton
        output = (toconvert*lbtoGram)/(lbtoOz*kgtoGram*tonStdtoKg); 
    }
    else if (unitbefore == 5 && unitafter == 2){
        //ounce -> US ton
        output = toconvert/(lbtoOz*tonUStoLb); 
    }
    else if (unitbefore == 5 && unitafter == 3){
        //ounce -> UK ton
        output = toconvert/(lbtoOz*tonUKtoLb); 
    }
    else if (unitbefore == 5 && unitafter == 4){
        //ounce -> pound
        output = toconvert/lbtoOz; 
    }
    else if (unitbefore == 5 && unitafter == 6){
        //ounce -> kilogram
        output = (toconvert*lbtoGram)/(lbtoOz*kgtoGram); 
    }
    else if (unitbefore == 5 && unitafter == 7){
        //ounce -> gram
        output = (toconvert*lbtoGram)/(lbtoOz); 
    }
    else if (unitbefore == 5 && unitafter == 8){
        //ounce -> milligram
        output = (toconvert*lbtoGram*gramtomg)/(lbtoOz); 
    }
     else if (unitbefore == 6 && unitafter == 1){
        //kilogram -> standard ton
        output = toconvert/tonStdtoKg; 
    }
    else if (unitbefore == 6 && unitafter == 2){
        //kilogram -> US ton
        output = toconvert*kgtoGram/(lbtoGram*tonUStoLb); 
    }
    else if (unitbefore == 6 && unitafter == 3){
        //kilogram -> UK ton
        output = toconvert*kgtoGram/(lbtoGram*tonUKtoLb); 
    }
    else if (unitbefore == 6 && unitafter == 4){
        //kilogram -> pound
        output = toconvert*kgtoGram/lbtoGram; 
    }
    else if (unitbefore == 6 && unitafter == 5){
        //kilogram -> ounce
        output = toconvert*kgtoGram*lbtoOz/lbtoGram; 
    }
    else if (unitbefore == 6 && unitafter == 7){
        //kilogram -> gram
        output = toconvert * kgtoGram; 
    }
    else if (unitbefore == 6 && unitafter == 8){
        //kilogram -> milligram
        output = toconvert * kgtoGram * gramtomg; 
    }
    else if (unitbefore == 7 && unitafter == 1){
        //gram -> standard ton
        output = toconvert/(kgtoGram*tonStdtoKg); 
    }
    else if (unitbefore == 7 && unitafter == 2){
        //gram -> US ton
        output = toconvert/(lbtoGram*tonUStoLb); 
    }
    else if (unitbefore == 7 && unitafter == 3){
        //gram -> UK ton
        output = toconvert/(lbtoGram*tonUKtoLb); 
    }
    else if (unitbefore == 7 && unitafter == 4){
        //gram -> pound
        output = toconvert/lbtoGram; 
    }
    else if (unitbefore == 7 && unitafter == 5){
        //gram -> ounce
        output = toconvert*lbtoOz/lbtoGram; 
    }
    else if (unitbefore == 7 && unitafter == 6){
        //gram -> kilogram
        output = toconvert/kgtoGram; 
    }
    else if (unitbefore == 7 && unitafter == 8){
        //gram -> milligram
        output = toconvert*gramtomg; 
    }
     else if (unitbefore == 8 && unitafter == 1){
        //milligram -> standard ton
        output = toconvert/(gramtomg*kgtoGram*tonStdtoKg); 
    }
    else if (unitbefore == 8 && unitafter == 2){
        //milligram -> US ton
        output = toconvert/(gramtomg*lbtoGram*tonUStoLb); 
    }
    else if (unitbefore == 8 && unitafter == 3){
        //milligram -> UK ton
        output = toconvert/(gramtomg*lbtoGram*tonUKtoLb); 
    }
    else if (unitbefore == 8 && unitafter == 4){
        //milligram -> pound
        output = toconvert/(gramtomg*lbtoGram);
    }
    else if (unitbefore == 8 && unitafter == 5){
        //milligram -> ounce
        output = toconvert*lbtoOz/(gramtomg*lbtoGram); 
    }
    else if (unitbefore == 8 && unitafter == 6){
        //milligram -> kilogram
        output = toconvert/(gramtomg*kgtoGram); 
    }
    else if (unitbefore == 8 && unitafter == 7){
        //milligram -> gram
        output = toconvert/(gramtomg); 
    }
    else{
        //default case
        cout <<"It should not happen!" <<endl; 
        output = -1.0;
    }
    return output;
}

//Length conversion
void lengthCalc(){
    cout << "Length conversion calculator" <<endl;
    
    int beforeChange, afterChange;
    double toConvert, afterConvert;
    string unitBeforeChange, unitAfterChange;
    string statement;
    bool toEnd = false;
    while (!toEnd){
        cout << "Type corresponding number to make your choice" <<endl;
        cout << "1. millimeters (mm)" << endl;
        cout << "2. centimeters (cm)" << endl;
        cout << "3. meters (m)" << endl;
        cout << "4. kilometers (km)" << endl;
        cout << "5. inches (in)" << endl;
        cout << "6. feet (ft)" << endl;
        cout << "7. yards (yd)" <<endl;
        cout << "8. miles (mi)" <<endl;
        cout << "9. nautical miles (nm)" <<endl;
        cout << "10. mils (mil)" <<endl;
        cout << "0. exit" <<endl;

        cout << "Which unit do you want to convert from?" << endl;
        cin >> beforeChange;
        unitBeforeChange = numtoLengthunit(beforeChange, toEnd);
        if(toEnd) break;
        
        cout << "What is the value to convert in " << unitBeforeChange << endl;
        cin >> toConvert;

        cout << "Which unit do you want to convert to?" << endl;
        cin >> afterChange;
        unitAfterChange = numtoLengthunit(afterChange, toEnd);
        if(toEnd) break;

        afterConvert = lengthConversion(beforeChange,afterChange,toConvert);
        if (afterConvert<0){
            toEnd = true; 
            break;
        }   
        //Enable this if there is a plan to save history with filestream
        //statement = to_string(toConvert) + " " + unitBeforeChange +" is converted into " + to_string(afterConvert) + " " + unitAfterChange;
        cout << setprecision(2) << toConvert << " " << unitBeforeChange << " is converted into " << setprecision(2) << afterConvert << " " << unitAfterChange <<endl;
    }
    cout << "Returning back to selection menu..." <<endl;
}

string numtoLengthunit(int input, bool & toEnd){
    string output;
    switch (input){
        case 0:
            output = "";
            toEnd = true;
            break;
        case 1: output = "millimeters (mm)"; break;
        case 2: output = "centimeters (cm)"; break;
        case 3: output = "meters (m)"; break;
        case 4: output = "kilometers (km)"; break;
        case 5: output = "inches (in)"; break;
        case 6: output = "feet (ft)"; break;
        case 7: output = "yards (yd)"; break;
        case 8: output = "miles (mi)"; break;
        case 9: output = "nautical miles (nm)"; break;
        case 10: output = "mils (mil)"; break;
        default:
            cout << "Invalid input!" <<endl;
            output = "";
            break;
    }
    return output;
}

double lengthConversion(int unitbefore, int unitafter, double toconvert){
    double output;
    if (unitbefore == unitafter){
        //when unit before = unit after
        output = toconvert;
    }
    else if (unitbefore == 1 && unitafter == 2){
        //mm to cm
        output = toconvert/cmtomm;
    }
    else if (unitbefore == 1 && unitafter == 3){
        //mm to m
        output = toconvert/(mtocm*cmtomm);
    }
    else if (unitbefore == 1 && unitafter == 4){
        //mm to km
        output = toconvert/(kmtom*mtocm*cmtomm);
    }
    else if (unitbefore == 1 && unitafter == 5){
        //mm to in
        output = toconvert/(cmtomm*intocm);
    }
    else if (unitbefore == 1 && unitafter == 6){
        //mm to ft
        output = toconvert/(cmtomm*intocm*fttoin);
    }
    else if (unitbefore == 1 && unitafter == 7){
        //mm to yd
        output = toconvert/(cmtomm*intocm*fttoin*ydtoft);
    }
    else if (unitbefore == 1 && unitafter == 8){
        //mm to mi
        output = toconvert/(cmtomm*intocm*fttoin*ydtoft*miletoyd);
    }
    else if (unitbefore == 1 && unitafter == 9){
        //mm to nautical miles
        output = toconvert/(cmtomm*mtocm*nauticaltometer);
    }
    else if (unitbefore == 1 && unitafter == 10){
        //mm to mils
        output = toconvert*intomil/(cmtomm*intocm);
    }
    else if (unitbefore == 2 && unitafter == 1){
        //cm to mm
        output = toconvert*cmtomm;
    }
    else if (unitbefore == 2 && unitafter == 3){
        //cm to m
        output = toconvert/(mtocm);
    }
    else if (unitbefore == 2 && unitafter == 4){
        //cm to km
        output = toconvert/(mtocm*kmtom);
    }
    else if (unitbefore == 2 && unitafter == 5){
        //cm to in
        output = toconvert/intocm;
    }
    else if (unitbefore == 2 && unitafter == 6){
        //cm to ft
        output = toconvert/(intocm*fttoin);
    }
    else if (unitbefore == 2 && unitafter == 7){
        //cm to yd
        output = toconvert/(intocm*fttoin*ydtoft);
    }
    else if (unitbefore == 2 && unitafter == 8){
        //cm to mi
        output = toconvert/(intocm*fttoin*ydtoft*miletoyd);
    }
    else if (unitbefore == 2 && unitafter == 9){
        //cm to nautical miles
        output = toconvert/(mtocm*nauticaltometer);
    }
    else if (unitbefore == 2 && unitafter == 10){
        //cm to mil
        output = toconvert*intomil/(intocm);
    }
    else if (unitbefore == 3 && unitafter == 1){
        //m to mm
        output = toconvert*mtocm*cmtomm;
    }
    else if (unitbefore == 3 && unitafter == 2){
        //m to cm
        output = toconvert*mtocm;
    }
    else if (unitbefore == 3 && unitafter == 4){
        //m to km
        output = toconvert/kmtom;
    }
    else if (unitbefore == 3 && unitafter == 5){
        //m to in
        output = toconvert*mtocm/intocm;
    }
    else if (unitbefore == 3 && unitafter == 6){
        //m to ft
        output = toconvert*mtocm/(intocm*fttoin);
    }
    else if (unitbefore == 3 && unitafter == 7){
        //m to yd
        output = toconvert*mtocm/(intocm*fttoin*ydtoft);
    }
    else if (unitbefore == 3 && unitafter == 8){
        //m to mi
        output = toconvert*mtocm/(intocm*fttoin*ydtoft*miletoyd);
    }
    else if (unitbefore == 3 && unitafter == 9){
        //m to nautical mile
        output = toconvert/nauticaltometer;
    }
    else if (unitbefore == 3 && unitafter == 10){
        //m to mil
        output = toconvert*mtocm*intomil/intocm;
    }
    else if (unitbefore == 4 && unitafter == 1){
        //km to mm
        output = toconvert*kmtom*mtocm*cmtomm;
    }
    else if (unitbefore == 4 && unitafter == 2){
        //km to cm
        output = toconvert*kmtom*mtocm;
    }
    else if (unitbefore == 4 && unitafter == 3){
        //km to m
        output = toconvert*kmtom;
    }
    else if (unitbefore == 4 && unitafter == 5){
        //km to in
        output = toconvert*kmtom*mtocm/intocm;
    }
    else if (unitbefore == 4 && unitafter == 6){
        //km to ft
        output = toconvert*kmtom*mtocm/(intocm*fttoin);
    }
    else if (unitbefore == 4 && unitafter == 7){
        //km to yd
        output = toconvert*kmtom*mtocm/(intocm*fttoin*ydtoft);
    }
    else if (unitbefore == 4 && unitafter == 8){
        //km to mi
        output = toconvert*kmtom*mtocm/(intocm*fttoin*ydtoft*miletoyd);
    }
    else if (unitbefore == 4 && unitafter == 9){
        //km to nautical miles
        output = toconvert*kmtom/nauticaltometer;
    }
    else if (unitbefore == 4 && unitafter == 10){
        //km to mil
        output = toconvert*kmtom*mtocm*intomil/intocm;
    }
    else if (unitbefore == 5 && unitafter == 1){
        //in to mm
        output = toconvert*intocm*cmtomm;
    }
    else if (unitbefore == 5 && unitafter == 2){
        //in to cm
        output = toconvert*intocm;
    }
    else if (unitbefore == 5 && unitafter == 3){
        //in to m
        output = toconvert*intocm/mtocm;
    }
    else if (unitbefore == 5 && unitafter == 4){
        //in to km
        output = toconvert*intocm/(mtocm*kmtom);
    }
    else if (unitbefore == 5 && unitafter == 6){
        //in to ft
        output = toconvert/fttoin;
    }
    else if (unitbefore == 5 && unitafter == 7){
        //in to yd
        output = toconvert/(fttoin*ydtoft);
    }
    else if (unitbefore == 5 && unitafter == 8){
        //in to mi
        output = toconvert/(fttoin*ydtoft*miletoyd);
    }
    else if (unitbefore == 5 && unitafter == 9){
        //in to nautical mile
        output = toconvert*intocm/(mtocm*nauticaltometer);
    }
    else if (unitbefore == 5 && unitafter == 10){
        //in to mil
        output = toconvert/intomil;
    }
    else if (unitbefore == 6 && unitafter == 1){
        //ft to mm
        output = toconvert*fttoin*intocm*cmtomm;
    }
    else if (unitbefore == 6 && unitafter == 2){
        //ft to cm
        output = toconvert*fttoin*intocm;
    }
    else if (unitbefore == 6 && unitafter == 3){
        //ft to m
        output = toconvert*fttoin*intocm/mtocm;
    }
    else if (unitbefore == 6 && unitafter == 4){
        //ft to km
        output = toconvert*fttoin*intocm/(kmtom*mtocm);
    }
    else if (unitbefore == 6 && unitafter == 5){
        //ft to in
        output = toconvert*fttoin;
    }
    else if (unitbefore == 6 && unitafter == 7){
        //ft to yd
        output = toconvert/ydtoft;
    }
    else if (unitbefore == 6 && unitafter == 8){
        //ft to mi
        output = toconvert/(ydtoft*miletoyd);
    }
    else if (unitbefore == 6 && unitafter == 9){
        //ft to nautical miles
        output = toconvert*fttoin*intocm/(mtocm*nauticaltometer);
    }
    else if (unitbefore == 6 && unitafter == 10){
        //ft to mil
        output = toconvert*fttoin*intomil;
    }
    else if (unitbefore == 7 && unitafter == 1){
        //yd to mm
        output = toconvert*ydtoft*fttoin*intocm*cmtomm;
    }
    else if (unitbefore == 7 && unitafter == 2){
        //yd to cm
        output = toconvert*ydtoft*fttoin*intocm;
    }
    else if (unitbefore == 7 && unitafter == 3){
        //yd to m
        output = toconvert*ydtoft*fttoin*intocm/mtocm;
    }
    else if (unitbefore == 7 && unitafter == 4){
        //yd to km
        output = toconvert*ydtoft*fttoin*intocm/(mtocm*kmtom);
    }
    else if (unitbefore == 7 && unitafter == 5){
        //yd to in
        output = toconvert*ydtoft*fttoin;
    }
    else if (unitbefore == 7 && unitafter == 6){
        //yd to ft
        output = toconvert*ydtoft;
    }
    else if (unitbefore == 7 && unitafter == 8){
        //yd to mi
        output = toconvert/miletoyd;
    }
    else if (unitbefore == 7 && unitafter == 9){
        //yd to nautical miles
        output = toconvert*ydtoft*fttoin*intocm/(mtocm*nauticaltometer);
    }
    else if (unitbefore == 7 && unitafter == 10){
        //yd to mil
        output = toconvert*ydtoft*fttoin*intomil;
    }
    else if (unitbefore == 8 && unitafter == 1){
        //mi to mm
        output = toconvert*miletoyd*ydtoft*fttoin*intocm*cmtomm;
    }
    else if (unitbefore == 8 && unitafter == 2){
        //mi to cm
        output = toconvert*miletoyd*ydtoft*fttoin*intocm;
    }
    else if (unitbefore == 8 && unitafter == 3){
        //mi to m
        output = toconvert*miletoyd*ydtoft*fttoin*intocm/mtocm;
    }
    else if (unitbefore == 8 && unitafter == 4){
        //mi to km
        output = toconvert*miletoyd*ydtoft*fttoin*intocm/(mtocm*kmtom);
    }
    else if (unitbefore == 8 && unitafter == 5){
        //mi to in
        output = toconvert*miletoyd*ydtoft*fttoin;
    }
    else if (unitbefore == 8 && unitafter == 6){
        //mi to ft
        output = toconvert*miletoyd*ydtoft;
    }
    else if (unitbefore == 8 && unitafter == 7){
        //mi to yd
        output = toconvert*miletoyd;
    }
    else if (unitbefore == 8 && unitafter == 9){
        //mi to nautical miles
        output = toconvert*miletoyd*ydtoft*fttoin*intocm/(mtocm*nauticaltometer);
    }
    else if (unitbefore == 8 && unitafter == 10){
        //mi to mil
        output = toconvert*miletoyd*ydtoft*fttoin*intomil;
    }
    else if (unitbefore == 9 && unitafter == 1){
        //nautical mile to mm
        output = toconvert*nauticaltometer*mtocm*cmtomm;
    }
    else if (unitbefore == 9 && unitafter == 2){
        //nautical mile to cm
        output = toconvert*nauticaltometer*mtocm;
    }
    else if (unitbefore == 9 && unitafter == 3){
        //nautical mile to m
        output = toconvert*nauticaltometer;
    }
    else if (unitbefore == 9 && unitafter == 4){
        //nautical mile to km
        output = toconvert*nauticaltometer/kmtom;
    }
    else if (unitbefore == 9 && unitafter == 5){
        //nautical mile to in
        output = toconvert*nauticaltometer*mtocm/intocm;
    }
    else if (unitbefore == 9 && unitafter == 6){
        //nautical mile to ft
        output = toconvert*nauticaltometer*mtocm/(intocm*fttoin);
    }
    else if (unitbefore == 9 && unitafter == 7){
        //nautical mile to yd
        output = toconvert*nauticaltometer*mtocm/(intocm*fttoin*ydtoft);
    }
    else if (unitbefore == 9 && unitafter == 8){
        //nautical mile to mi
        output = toconvert*nauticaltometer*mtocm/(intocm*fttoin*ydtoft*miletoyd);
    }
    else if (unitbefore == 9 && unitafter == 10){
        //nautical mile to mil
        output = toconvert*nauticaltometer*mtocm*intomil/(intocm);
    }
    else if (unitbefore == 10 && unitafter == 1){
        //mil to mm
        output = toconvert*intocm*cmtomm/(intomil);
    }
    else if (unitbefore == 10 && unitafter == 2){
        //mil to cm
        output = toconvert*intocm/(intomil);
    }
    else if (unitbefore == 10 && unitafter == 3){
        //mil to m
        output = toconvert*intocm/(intomil*mtocm);
    }
    else if (unitbefore == 10 && unitafter == 4){
        //mil to km
        output = toconvert*intocm/(intomil*mtocm*kmtom);
    }
    else if (unitbefore == 10 && unitafter == 5){
        //mil to in
        output = toconvert/intomil;
    }
    else if (unitbefore == 10 && unitafter == 6){
        //mil to ft
        output = toconvert/(intomil*fttoin);
    }
    else if (unitbefore == 10 && unitafter == 7){
        //mil to yd
        output = toconvert/(intomil*fttoin*ydtoft);
    }
    else if (unitbefore == 10 && unitafter == 8){
        //mil to mi
        output = toconvert/(intomil*fttoin*ydtoft*miletoyd);
    }
    else if (unitbefore == 10 && unitafter == 9){
        //mil to nautical mile
        output = toconvert*intocm/(intomil*mtocm*nauticaltometer);
    }
    else{
        //default case
        cout <<"It should not happen!" <<endl; 
        output = -1.0;
    }
    return output;
}

//currency conversion
void currencyCalc(){

}

//area conversion
void areaCalc(){
    cout << "Area conversion calculator" <<endl;
    
    int beforeChange, afterChange;
    double toConvert, afterConvert;
    string unitBeforeChange, unitAfterChange;
    string statement;
    bool toEnd = false;
    while (!toEnd){
        cout << "Type corresponding number to make your choice" <<endl;
        cout << "1. acres (ac)" << endl;
        cout << "2. ares (a)" << endl;
        cout << "3. hectares (ha)" << endl;
        cout << "4. square millimeters (mm^2)" << endl;
        cout << "5. square centimeters (cm^2)" << endl;
        cout << "6. square meters (m^2)" << endl;
        cout << "7. square kilometers (km^2)" <<endl;
        cout << "8. square inches (in^2)" <<endl;
        cout << "9. square feet (ft^2)" <<endl;
        cout << "10. square yards (yd^2)" <<endl;
        cout << "11. square miles (mi^2)" <<endl;
        cout << "0. exit" <<endl;

        cout << "Which unit do you want to convert from?" << endl;
        cin >> beforeChange;
        unitBeforeChange = numtoAreaunit(beforeChange, toEnd);
        if(toEnd) break;
        
        cout << "What is the value to convert in " << unitBeforeChange << endl;
        cin >> toConvert;

        cout << "Which unit do you want to convert to?" << endl;
        cin >> afterChange;
        unitAfterChange = numtoAreaunit(afterChange, toEnd);
        if(toEnd) break;

        afterConvert = areaConversion(beforeChange,afterChange,toConvert);
        if (afterConvert<0){
            toEnd = true; 
            break;
        }   
        //Enable this if there is a plan to save history with filestream
        //statement = to_string(toConvert) + " " + unitBeforeChange +" is converted into " + to_string(afterConvert) + " " + unitAfterChange;
        cout << setprecision(2) << toConvert << " " << unitBeforeChange << " is converted into " << setprecision(2) << afterConvert << " " << unitAfterChange <<endl;
    }
    cout << "Returning back to selection menu..." <<endl;
}

string numtoAreaunit(int input, bool & toEnd){
    string output;
    switch (input){
        case 0:
            output = "";
            toEnd = true;
            break;
        case 1: output = "acres (ac)"; break;
        case 2: output = "ares (a)"; break;
        case 3: output = "hectares (ha)"; break;
        case 4: output = "square millimeters (mm^2)"; break;
        case 5: output = "square centimeters (cm^2)"; break;
        case 6: output = "square meters (m^2)"; break;
        case 7: output = "square kilometers (km^2)"; break;
        case 8: output = "square inches (in^2)"; break;
        case 9: output = "square feet (ft^2)"; break;
        case 10: output = "square yards (yd^2)"; break;
        case 11: output = "square miles (mi^2)"; break;
        default:
            cout << "Invalid input!" <<endl;
            output = "";
            break;
    }
    return output;
}

double areaConversion(int unitbefore, int unitafter, double toconvert){
    double output;
    if (unitbefore == unitafter){
        //when unit before = unit after
        output = toconvert;
    }
    else if (unitbefore == 1 && unitafter == 2){
        //acre -> are
        output = toconvert*acretosqft*sqfttosqin*sqintosqcm*hectaretoare/(sqmtosqcm*hectaretosqm); 
    }
    else if (unitbefore == 1 && unitafter == 3){
        //acre -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 4){
        //acre -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 5){
        //acre -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 6){
        //acre -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 7){
        //acre -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 8){
        //acre -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 9){
        //acre -> sqft
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 10){
        //acre ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 11){
        //acre -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 1){
        //are -> acre
        output = toconvert*(sqmtosqcm*hectaretosqm)/(acretosqft*sqfttosqin*sqintosqcm*hectaretoare); 
    }
    else if (unitbefore == 2 && unitafter == 3){
        //are -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 4){
        //are -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 5){
        //are -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 6){
        //are -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 7){
        //are -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 8){
        //are -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 9){
        //are -> sqft
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 10){
        //are ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 11){
        //are -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 1){
        //hectare -> acre
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 2){
        //hectare -> are
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 4){
        //hectare -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 5){
        //hectare -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 6){
        //hectare -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 7){
        //hectare -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 8){
        //hectare -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 9){
        //hectare -> sqft
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 10){
        //hectare ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 11){
        //hectare -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 1){
        //sqmm -> acre
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 2){
        //sqmm -> are
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 3){
        //sqmm -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 5){
        //sqmm -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 6){
        //sqmm -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 7){
        //sqmm -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 8){
        //sqmm -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 9){
        //sqmm -> sqft
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 10){
        //sqmm ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 11){
        //sqmm -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 1){
        //sqcm -> acre
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 2){
        //sqcm -> are
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 3){
        //sqcm -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 4){
        //sqcm -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 6){
        //sqcm -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 7){
        //sqcm -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 8){
        //sqcm -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 9){
        //sqcm -> sqft
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 10){
        //sqcm ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 11){
        //sqcm -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 1){
        //sqm -> acre
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 2){
        //sqm -> are
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 3){
        //sqm -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 4){
        //sqm -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 5){
        //sqm -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 7){
        //sqm -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 8){
        //sqm -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 9){
        //sqm -> sqft
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 10){
        //sqm ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 11){
        //sqm -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 1){
        //sqkm -> acre
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 2){
        //sqkm -> are
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 3){
        //sqkm -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 4){
        //sqkm -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 5){
        //sqkm -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 6){
        //sqkm -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 8){
        //sqkm -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 9){
        //sqkm -> sqft
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 10){
        //sqkm ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 11){
        //sqkm -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 1){
        //sqin -> acre
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 2){
        //sqin -> are
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 3){
        //sqin -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 4){
        //sqin -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 5){
        //sqin -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 6){
        //sqin -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 7){
        //sqin -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 9){
        //sqin -> sqft
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 10){
        //sqin ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 11){
        //sqin -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 1){
        //sqft -> acre
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 2){
        //sqft -> are
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 3){
        //sqft -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 4){
        //sqft -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 5){
        //sqft -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 6){
        //sqft -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 7){
        //sqft -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 8){
        //sqft -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 10){
        //sqft ->sqyd
        output = toconvert; 
    }
    else if (unitbefore == 9 && unitafter == 11){
        //sqft -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 1){
        //sqyd -> acre
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 2){
        //sqyd -> are
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 3){
        //sqyd -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 4){
        //sqyd -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 5){
        //sqyd -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 6){
        //sqyd -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 7){
        //sqyd -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 8){
        //sqyd -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 9){
        //sqyd ->sqft
        output = toconvert; 
    }
    else if (unitbefore == 10 && unitafter == 11){
        //sqyd -> sqmi
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 1){
        //sqmi -> acre
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 2){
        //sqmi -> are
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 3){
        //sqmi -> hectare
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 4){
        //sqmi -> sqmm
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 5){
        //sqmi -> sqcm
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 6){
        //sqmi -> sqm
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 7){
        //sqmi -> sqkm
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 8){
        //sqmi -> sqin
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 9){
        //sqmi ->sqft
        output = toconvert; 
    }
    else if (unitbefore == 11 && unitafter == 10){
        //sqmi -> sqyd
        output = toconvert; 
    }
    else{
        //default case
        cout <<"It should not happen!" <<endl; 
        output = -1.0;
    }
    return output;
}

//temperature conversion
void temperatureCalc(){
    cout << "Temperature conversion calculator" <<endl;
    
    int beforeChange, afterChange;
    double toConvert, afterConvert;
    string unitBeforeChange, unitAfterChange;
    string statement;
    bool toEnd = false;
    while (!toEnd){
        cout << "Type corresponding number to make your choice" <<endl;
        cout << "1. celsius (C)" << endl;
        cout << "2. kelvin (K)" << endl;
        cout << "3. fahrenheit (F)" << endl;
        cout << "0. exit" <<endl;

        cout << "Which unit do you want to convert from?" << endl;
        cin >> beforeChange;
        unitBeforeChange = numtoTemperatureunit(beforeChange, toEnd);
        if(toEnd) break;
        
        cout << "What is the value to convert in " << unitBeforeChange << endl;
        cin >> toConvert;

        cout << "Which unit do you want to convert to?" << endl;
        cin >> afterChange;
        unitAfterChange = numtoTemperatureunit(afterChange, toEnd);
        if(toEnd) break;

        afterConvert = temperatureConversion(beforeChange,afterChange,toConvert);
        if (afterConvert<-460){
            //The lowest in fahrenheit is -459.67. I just gave some offset. It will be edited when physics change
            toEnd = true; 
            break;
        }   
        //Enable this if there is a plan to save history with filestream
        //statement = to_string(toConvert) + " " + unitBeforeChange +" is converted into " + to_string(afterConvert) + " " + unitAfterChange;
        cout << setprecision(2) << toConvert << " " << unitBeforeChange << " is converted into " << setprecision(2) << afterConvert << " " << unitAfterChange <<endl;
    }
    cout << "Returning back to selection menu..." <<endl;
}

string numtoTemperatureunit(int input, bool & toEnd){
    string output;
    switch (input){
        case 0:
            output = "";
            toEnd = true;
            break;
        case 1: output = "celsius (C)"; break;
        case 2: output = "kelvin (K)"; break;
        case 3: output = "fahrenheit (F)"; break;
        default:
            cout << "Invalid input!" <<endl;
            output = "";
            break;
    }
    return output;
}

double temperatureConversion(int unitbefore, int unitafter, double toconvert){
    double output;
    if (unitbefore == unitafter){
        //when unit before = unit after
        output = toconvert;
    }
    else if (unitbefore == 1 && unitafter == 2){
        //C -> K
        output = toconvert+273.15; 
    }
    else if (unitbefore == 1 && unitafter == 3){
        //C -> F
        output = toconvert*1.8 + 32; 
    }
    else if (unitbefore == 2 && unitafter == 1){
        //K -> C
        output = toconvert-273.15; 
    }
    else if (unitbefore == 2 && unitafter == 3){
        //K -> F
        output = (toconvert-273.15)*1.8+32; 
    }
    else if (unitbefore == 3 && unitafter == 1){
        //F -> C
        output = (toconvert-32)/1.8; 
    }
    else if (unitbefore == 3 && unitafter == 2){
        //F -> K
        output = ((toconvert-32)/1.8)-273.15; 
    }
    else{
        //default case
        cout <<"It should not happen!" <<endl; 
        output = -500.0;
    }
    return output;
}

//data conversion
void dataCalc(){
    cout << "Data conversion calculator" <<endl;
    
    int beforeChange, afterChange;
    double toConvert, afterConvert;
    string unitBeforeChange, unitAfterChange;
    string statement;
    bool toEnd = false;
    while (!toEnd){
        cout << "Type corresponding number to make your choice" <<endl;
        cout << "1. bit" << endl;
        cout << "2. byte" << endl;
        cout << "3. kilobyte (KiB)" << endl;
        cout << "4. megabyte (MiB)" << endl;
        cout << "5. gigabyte (GiB)" << endl;
        cout << "6. terabyte (TiB)" << endl;
        cout << "7. petabyte (PiB)" << endl;
        cout << "8. exabyte (EiB)" << endl;
        cout << "0. exit" <<endl;

        cout << "Which unit do you want to convert from?" << endl;
        cin >> beforeChange;
        unitBeforeChange = numtoDataunit(beforeChange, toEnd);
        if(toEnd) break;
        
        cout << "What is the value to convert in " << unitBeforeChange << endl;
        cin >> toConvert;

        cout << "Which unit do you want to convert to?" << endl;
        cin >> afterChange;
        unitAfterChange = numtoDataunit(afterChange, toEnd);
        if(toEnd) break;

        afterConvert = dataConversion(beforeChange,afterChange,toConvert);
        if (afterConvert<0){
            toEnd = true; 
            break;
        }   
        //Enable this if there is a plan to save history with filestream
        //statement = to_string(toConvert) + " " + unitBeforeChange +" is converted into " + to_string(afterConvert) + " " + unitAfterChange;
        cout << setprecision(2) << toConvert << " " << unitBeforeChange << " is converted into " << setprecision(2) << afterConvert << " " << unitAfterChange <<endl;
    }
    cout << "Returning back to selection menu..." <<endl;
}

string numtoDataunit(int input, bool & toEnd){
    string output;
    switch (input){
        case 0:
            output = "";
            toEnd = true;
            break;
        case 1: output = "bit"; break;
        case 2: output = "byte"; break;
        case 3: output = "kilobyte (KiB)"; break;
        case 4: output = "megabyte (MiB)"; break;
        case 5: output = "gigabyte (GiB)"; break;
        case 6: output = "terabyte (TiB)"; break;
        case 7: output = "petabyte (PiB)"; break;
        case 8: output = "exabyte (EiB)"; break;
        default:
            cout << "Invalid input!" <<endl;
            output = "";
            break;
    }
    return output;
}

double dataConversion(int unitbefore, int unitafter, double toconvert){
    double output;
    if (unitbefore == unitafter){
        //when unit before = unit after
        output = toconvert;
    }
    else if (unitbefore == 1 && unitafter >= 2 && unitafter <= 8){
        //bit to kilobyte and other ~bytes
        output = toconvert/(bytetobit*pow(kbtobyte,unitafter-2)); 
    }
    else if (unitbefore >= 2 && unitbefore <=8 && unitafter >= 2 && unitafter <= 8){
        //byte to ~byte
        output = toconvert*(pow(kbtobyte,unitbefore-unitafter)); 
    }
    else if (unitbefore >= 2 && unitbefore <= 8 && unitafter == 1){
        //~byte to bit
        output = toconvert*bytetobit*(pow(kbtobyte,unitbefore-2)); 
    }
    else{
        //default case
        cout <<"It should not happen!" <<endl; 
        output = -1.0;
    }
    return output;
}

//speed conversion
void speedCalc(){

}

string numtoSpeedunit(int input, bool & toEnd){

}

double speedConversion(int unitbefore, int unitafter, double toconvert){
    double output;
    if (unitbefore == unitafter){
        //when unit before = unit after
        output = toconvert;
    }
    else if (unitbefore == 1 && unitafter == 2){
        //standard ton -> US ton
        output = toconvert*(tonStdtoKg*kgtoGram/lbtoGram)/tonUStoLb; 
    }
    else{
        //default case
        cout <<"It should not happen!" <<endl; 
        output = -1.0;
    }
    return output;
}

//time conversion
void timeCalc(){
    cout << "Time conversion calculator" <<endl;
    
    int beforeChange, afterChange;
    double toConvert, afterConvert;
    string unitBeforeChange, unitAfterChange;
    string statement;
    bool toEnd = false;
    while (!toEnd){
        cout << "Type corresponding number to make your choice" <<endl;
        cout << "1. ms (millisecond)" << endl;
        cout << "2. s (second)" << endl;
        cout << "3. m (minute)" << endl;
        cout << "4. h (hour)" << endl;
        cout << "5. d (day)" << endl;
        cout << "6. wk (week)" << endl;
        cout << "7. yr (year)" << endl;
        cout << "0. exit" <<endl;

        cout << "Which unit do you want to convert from?" << endl;
        cin >> beforeChange;
        unitBeforeChange = numtoDataunit(beforeChange, toEnd);
        if(toEnd) break;
        
        cout << "What is the value to convert in " << unitBeforeChange << endl;
        cin >> toConvert;

        cout << "Which unit do you want to convert to?" << endl;
        cin >> afterChange;
        unitAfterChange = numtoDataunit(afterChange, toEnd);
        if(toEnd) break;

        afterConvert = dataConversion(beforeChange,afterChange,toConvert);
        if (afterConvert<0){
            toEnd = true; 
            break;
        }   
        //Enable this if there is a plan to save history with filestream
        //statement = to_string(toConvert) + " " + unitBeforeChange +" is converted into " + to_string(afterConvert) + " " + unitAfterChange;
        cout << setprecision(2) << toConvert << " " << unitBeforeChange << " is converted into " << setprecision(2) << afterConvert << " " << unitAfterChange <<endl;
    }
    cout << "Returning back to selection menu..." <<endl;
}

string numtoTimeunit(int input, bool & toEnd){
    string output;
    switch (input){
        case 0:
            output = "";
            toEnd = true;
            break;
        case 1: output = "ms (millisecond)"; break;
        case 2: output = "s (second)"; break;
        case 3: output = "m (minute)"; break;
        case 4: output = "h (hour)"; break;
        case 5: output = "d (day)"; break;
        case 6: output = "wk (week)"; break;
        case 7: output = "yr (year)"; break;
        default:
            cout << "Invalid input!" <<endl;
            output = "";
            break;
    }
    return output;
}

double timeConversion(int unitbefore, int unitafter, double toconvert){
    double output;
    if (unitbefore == unitafter){
        //when unit before = unit after
        output = toconvert;
    }
    else if (unitbefore == 1 && unitafter == 2){
        //standard ton -> US ton
        output = toconvert; 
    }
    else{
        //default case
        cout <<"It should not happen!" <<endl; 
        output = -1.0;
    }
    return output;
}

//volume conversion
void volumeCalc(){
    cout << "Volume conversion calculator" <<endl;
    
    int beforeChange, afterChange;
    double toConvert, afterConvert;
    string unitBeforeChange, unitAfterChange;
    string statement;
    bool toEnd = false;
    while (!toEnd){
        cout << "Type corresponding number to make your choice" <<endl;
        cout << "1. gal (UK gallon)" << endl;
        cout << "2. gal (US gallon)" << endl;
        cout << "3. L (liters)" << endl;
        cout << "4. mL (milliliters)" << endl;
        cout << "5. cc (cubic centimeters)" << endl;
        cout << "6. m^3 (cubicmeters)" << endl;
        cout << "7. in^3 (cubic inches)" << endl;
        cout << "8. ft^3 (cubic feet)" << endl;
        cout << "0. exit" <<endl;

        cout << "Which unit do you want to convert from?" << endl;
        cin >> beforeChange;
        unitBeforeChange = numtoVolumeunit(beforeChange, toEnd);
        if(toEnd) break;
        
        cout << "What is the value to convert in " << unitBeforeChange << endl;
        cin >> toConvert;

        cout << "Which unit do you want to convert to?" << endl;
        cin >> afterChange;
        unitAfterChange = numtoVolumeunit(afterChange, toEnd);
        if(toEnd) break;

        afterConvert = volumeConversion(beforeChange,afterChange,toConvert);
        if (afterConvert<0){
            toEnd = true; 
            break;
        }   
        //Enable this if there is a plan to save history with filestream
        //statement = to_string(toConvert) + " " + unitBeforeChange +" is converted into " + to_string(afterConvert) + " " + unitAfterChange;
        cout << setprecision(2) << toConvert << " " << unitBeforeChange << " is converted into " << setprecision(2) << afterConvert << " " << unitAfterChange <<endl;
    }
    cout << "Returning back to selection menu..." <<endl;
}

string numtoVolumeunit(int input, bool & toEnd){
    string output;
    switch (input){
        case 0:
            output = "";
            toEnd = true;
            break;
        case 1: output = "gal (UK gallon)"; break;
        case 2: output = "gal (US gallon)"; break;
        case 3: output = "L (liters)"; break;
        case 4: output = "mL (milliliters)"; break;
        case 5: output = "cc (cubic centimeters)"; break;
        case 6: output = "m^3 (cubicmeters)"; break;
        case 7: output = "in^3 (cubic inches)"; break;
        case 8: output = "ft^3 (cubic feet)"; break;
        default:
            cout << "Invalid input!" <<endl;
            output = "";
            break;
    }
    return output;
}

double volumeConversion(int unitbefore, int unitafter, double toconvert){
    double output;
    if (unitbefore == unitafter){
        //when unit before = unit after
        output = toconvert;
    }
    else if (unitbefore == 1 && unitafter == 2){
        //gal (UK) -> gal (US)
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 3){
        //gal (UK) -> L (liters)
        output = toconvert;  
    }
    else if (unitbefore == 1 && unitafter == 4){
        //gal (UK) -> mL (milliliters)
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 5){
        //gal (UK) -> cc (cubic centimeters)
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 6){
        //gal (UK) -> m^3 (cubicmeters)
        output = toconvert; 
    }
    else if (unitbefore == 1 && unitafter == 7){
        //gal (UK) -> in^3 (cubic inches)
        output = toconvert;  
    }
    else if (unitbefore == 1 && unitafter == 8){
        //gal (UK) -> ft^3 (cubic feet)
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 1){
        //gal (US) -> gal (UK)
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 3){
        //gal (US) -> L (liters)
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 4){
        //gal (US) -> mL (milliliters)
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 5){
        //gal (US) -> cc (cubic centimeters)
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 6){
        //gal (US) -> m^3 (cubicmeters)
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 7){
        //gal (US) -> in^3 (cubic inches)
        output = toconvert; 
    }
    else if (unitbefore == 2 && unitafter == 8){
        //gal (US) -> ft^3 (cubic feet)
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 1){
        //L (liters) -> gal (UK)
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 2){
        //L (liters) -> gal (US)
        output = toconvert; 
    }
    else if (unitbefore == 3 && unitafter == 4){
        //L (liters) -> mL (milliliters)
        output = toconvert;
    }
    else if (unitbefore == 3 && unitafter == 5){
        //L (liters) -> cc (cubic centimeters)
        output = toconvert;
    }
    else if (unitbefore == 3 && unitafter == 6){
        //L (liters) -> m^3 (cubicmeters)
        output = toconvert;
    }
    else if (unitbefore == 3 && unitafter == 7){
        //L (liters) -> in^3 (cubic inches)
        output = toconvert;
    }
    else if (unitbefore == 3 && unitafter == 8){
        //L (liters) -> ft^3 (cubic feet)
        output = toconvert;
    }
     else if (unitbefore == 4 && unitafter == 1){
        //mL (milliliters) -> gal (UK)
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 2){
        //mL (milliliters) -> gal (US)
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 3){
        //mL (milliliters) -> L (liters)
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 5){
        //mL (milliliters) -> cc (cubic centimeters)
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 6){
        //mL (milliliters) -> m^3 (cubicmeters)
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 7){
        //mL (milliliters) -> in^3 (cubic inches)
        output = toconvert; 
    }
    else if (unitbefore == 4 && unitafter == 8){
        //mL (milliliters) -> ft^3 (cubic feet)
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 1){
        //cc (cubic centimeters) -> gal (UK)
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 2){
        //cc (cubic centimeters) -> gal (US)
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 3){
        //cc (cubic centimeters) -> L (liters)
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 4){
        //cc (cubic centimeters) -> mL (milliliters)
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 6){
        //cc (cubic centimeters) -> m^3 (cubicmeters)
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 7){
        //cc (cubic centimeters) -> in^3 (cubic inches)
        output = toconvert; 
    }
    else if (unitbefore == 5 && unitafter == 8){
        //cc (cubic centimeters) -> ft^3 (cubic feet)
        output = toconvert; 
    }
     else if (unitbefore == 6 && unitafter == 1){
        //m^3 (cubicmeters) -> gal (UK)
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 2){
        //m^3 (cubicmeters) -> gal (US)
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 3){
        //m^3 (cubicmeters) -> L (liters)
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 4){
        //m^3 (cubicmeters) -> mL (milliliters)
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 5){
        //m^3 (cubicmeters) -> cc (cubic centimeters)
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 7){
        //m^3 (cubicmeters) -> in^3 (cubic inches)
        output = toconvert; 
    }
    else if (unitbefore == 6 && unitafter == 8){
        //m^3 (cubicmeters) -> ft^3 (cubic feet)
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 1){
        //in^3 (cubic inches) -> gal (UK)
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 2){
        //in^3 (cubic inches) -> gal (US)
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 3){
        //in^3 (cubic inches) -> L (liters)
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 4){
        //in^3 (cubic inches) -> mL (milliliters)
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 5){
        //in^3 (cubic inches) -> cc (cubic centimeters)
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 6){
        //in^3 (cubic inches) -> m^3 (cubicmeters)
        output = toconvert; 
    }
    else if (unitbefore == 7 && unitafter == 8){
        //in^3 (cubic inches) -> ft^3 (cubic feet)
        output = toconvert; 
    }
     else if (unitbefore == 8 && unitafter == 1){
        //ft^3 (cubic feet) -> gal (UK)
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 2){
        //ft^3 (cubic feet) -> gal (US)
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 3){
        //ft^3 (cubic feet) -> L (liters)
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 4){
        //ft^3 (cubic feet) -> mL (milliliters)
        output = toconvert;
    }
    else if (unitbefore == 8 && unitafter == 5){
        //ft^3 (cubic feet) -> cc (cubic centimeters)
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 6){
        //ft^3 (cubic feet) -> m^3 (cubicmeters)
        output = toconvert; 
    }
    else if (unitbefore == 8 && unitafter == 7){
        //ft^3 (cubic feet) -> in^3 (cubic inches)
        output = toconvert; 
    }
    else{
        //default case
        cout <<"It should not happen!" <<endl; 
        output = -1.0;
    }
    return output;
}