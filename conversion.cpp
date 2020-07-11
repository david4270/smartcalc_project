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

//temperature conversion paramenters

//data conversion parameters

//speed conversion paramenters

//time conversion parameters

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

}

//temperature conversion
void temperatureCalc(){

}

//data conversion
void dataCalc(){

}

//speed conversion
void speedCalc(){

}

//time conversion
void timeCalc(){

}