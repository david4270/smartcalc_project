#include "scicalc.h"
#include "eqncalc.h"
#include "conversion.h"
using namespace std;

//SmartCalc - Everything of the calculation
//Version 0.1 (200708)

//To compile the program:
//g++ main.cpp scicalc.cpp eqncalc.cpp conversion.cpp -o scicalc.exe

void calcFeature();

int main(){
    calcFeature();
    return 0;
}

void calcFeature(){
    int featureToExecute;
    bool toEnd = false;
    while (!toEnd){
        cout << "Welcome to smartCalc!" <<endl;
        cout << "1. Scientific calculator" << endl;
        cout << "2. Conversion calculator" << endl;
        cout << "3. Graphing calculator" << endl;
        cout << "0. Exit program" <<endl;
        cout << endl;
        cout << "Type feature to execute: ";
        cin >> featureToExecute;
        if(featureToExecute == 1){
            sciCalc();
        }
        else if(featureToExecute == 2){
            conversionCalc();
        }
        else if(featureToExecute == 3){
            graphCalc();
        }
        else if(featureToExecute == 0){
            toEnd = true;
            cout << "Terminating calculator..."<<endl;
        }
        else{
            cout << "Error! Wrong input to execute. Try again..." <<endl;
        }
        cout << endl;
    }
}