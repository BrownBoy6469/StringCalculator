#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    bool notDone = true;
    string expression = "";
    string answer = "";
    while(notDone) {
        cout << ">> ";
        std::getline(cin, expression);
        if(expression == "quit" or expression == "q") {
            notDone = false;
        }
        else {
            int plusIndex = expression.find(' ');
            //cout << plusIndex << endl;
            string num1 = expression.substr(0,plusIndex);
            expression.erase(0,plusIndex + 1);
            char sign = expression.at(0);
            expression.erase(0,2);
            string num2 = expression;
            cout << endl;
            //cout << num1 << endl;
            //cout << sign << endl;
            //cout << num2 << endl;

            if(sign == '+') {
                answer = add(num1,num2);
            }
            else if(sign == '*') {
                answer = multiply(num1,num2);
            }
            else {
                throw std::invalid_argument("Invalid Argument in main");
            }

            cout << "ans =" << endl;
            cout << endl;
            cout << "    " << answer << endl;
            cout << endl;
        }
    }
    cout << endl;
    cout << "farvel!" << endl;
    cout << endl;
    return 0;
}

