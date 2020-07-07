#include "scicalc.h"
using namespace std;

//To compile the program:
//g++ main.cpp scicalc.cpp -o scicalc.exe

void calcFeature();

int main(){
    calcFeature();
    return 0;
}

void calcFeature(){
    string featureToExecute;
    bool toEnd = false;
    while (!toEnd){
        cout << "Type feature to execute: ";
        getline(cin, featureToExecute);
        if(featureToExecute == "s" || featureToExecute == "S"){
            sciCalc();
        }
        else if(featureToExecute == "e" || featureToExecute == "E"){
            toEnd = true;
            cout << "Terminating calculator..."<<endl;
        }
        else{
            cout << "Error! Wrong input to execute. Try again..." <<endl;
        }
        cout << endl;
    }
}