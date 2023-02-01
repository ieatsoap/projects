#include <iostream>
#include "trace.cpp"
using namespace std;

int main() {
    tint test = 5;              //Created   "5"
    test += 1;                  //Inc.      "6"
    cout << "test * 8 = " 
         << (test *= 8) << endl;//Mult.     "48"
    cout << "test / 3 = " 
         << (test /= 3) << endl;//Div.      "16"
    cout << "resulting history = "; test.log_history();

    cout << "-----------------------------------------------" << endl;

    test.roll_back(1);
    cout << "resulting value = " << test.i << endl;
    cout << "resulting history = ";
    //test.log_history(true);
    //roll value back 1. moved trimmed history to private vector versions

    cout << "-----------------------------------------------" << endl;

    cout << "The big one. remaking a 3-length collection until the versions form a matrix." << endl;

    tint newtest = -1; //-1 is never seen but always rolled back to.
                       //I prefer it as an anchor number when dealing with real #s
    for (int i = 0; i < 15; i ++) {
        cout << "\t" << newtest.i << endl;

        if (i%3==0 && !newtest.roll_back(3)) { cout << newtest.i << endl; }
        newtest = i;
    } //Data has been logged, now display history
    newtest.log_history(true); 

    //test.log_history();
    return 0;
}