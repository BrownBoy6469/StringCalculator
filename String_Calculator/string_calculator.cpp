#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // converts the char to an int
    // subtraction by 48 needed because '0' is a 48 in the ASCII table
    int decimal = (int)digit - 48;
    if(decimal < 0 or decimal > 9) {
        throw std::invalid_argument("Invalid Argument in digit_to_decimal");
    }
    return decimal;
}

char decimal_to_digit(unsigned int decimal) {
    if(decimal > 9) {
        throw std::invalid_argument("Invalid Argument in decimal_to_digit");
    }
    // converts int to char
    // we are adding by '0' in order to avoid typecasting
    char digit = '0' + decimal;
    return digit;
}

string trim_leading_zeros(string num) {
    // trims any leading zeroes
    // if num begins with a '-' it gets removed then is added it back at the end
    bool isSign = false;
    if(num.at(0) == '-') {
        isSign = true;
        num.erase(0,1);
    }
    bool notDone = true;
    while(notDone) {
        if(num.at(0) == '0' and num.length() == 1) {
            isSign = false;
            notDone = false;
        }
        else if(num.at(0) == '0') {
            num.erase(0,1);
        }
        else {
            notDone = false;
        }
    }
    if(isSign == true) {
        num.insert(0,"-");
    }
    return num;
}

string add(string lhs, string rhs) {
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    bool isSign = false;
    if(lhs.at(0) == '-') {
        isSign = true;
        lhs.erase(0,1);
    }
    if(rhs.at(0) == '-') {
        isSign = true;
        rhs.erase(0,1);
    }

    bool notSameLength = true;
    while(notSameLength) {
        if(lhs.length() > rhs.length()) {
            rhs.insert(0,"0");
        }
        else if(lhs.length() < rhs.length()) {
            lhs.insert(0,"0");
        }
        else {
            notSameLength = false;
        }
    }

    lhs.insert(0,"0");
    rhs.insert(0,"0");
    int sum = 0;
    int a = 0;
    int b = 0;
    int carry = 0;
    string newNum = "";

    for(int i = lhs.length() - 1; i >= 0; i--) {
        a = digit_to_decimal(lhs.at(i));
        b = digit_to_decimal(rhs.at(i));

        sum = a + b + carry;
        if(sum >= 10) {
            carry = 1;
            sum %= 10;
        }
        else {
            carry = 0;
        }
        newNum.insert(0, 1,decimal_to_digit(sum));
    }

    if(isSign) {
        newNum.insert(0,"-");
    }
    newNum = trim_leading_zeros(newNum);

    return newNum;
}

string multiply(string lhs, string rhs) {
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    bool isSign = false;
    if(lhs.at(0) == '-' and rhs.at(0) == '-') {
        lhs.erase(0,1);
        rhs.erase(0,1);
    }
    else if(lhs.at(0) == '-') {
        isSign = true;
        lhs.erase(0,1);
    }
    else if(rhs.at(0) == '-') {
        isSign = true;
        rhs.erase(0,1);
    }

    int product = 0;
    int a = 0;
    int b = 0;
    int carry = 0;
    int numExtraZero = 0;
    string num1 = "";
    string num2 = "0";

    for(int i = rhs.length() - 1; i >= 0; i--) {
        a = digit_to_decimal(rhs.at(i));

        for(int k = 0; k < numExtraZero; k++) {
            num1.push_back('0');
        }
        //cout << "A " << a << endl;
        for(int j = lhs.length() - 1; j >= 0; j--) {
            b = digit_to_decimal(lhs.at(j));
            //cout << "B " << b << endl;
            product = (a * b) + carry;
            if(product >= 10) {
                carry = product / 10;
                product %= 10;
            }
            else {
                carry = 0;
            }
            //cout << "Pushing Digit: " << decimal_to_digit(product) << endl;
            num1.insert(0, 1, decimal_to_digit(product));
        }

        num1.insert(0, 1, decimal_to_digit(carry));
        num1 = trim_leading_zeros(num1);
        //cout << "Num1: " << num1 << endl;       
        num2 = add(num1,num2);
        //cout << "Num2: " << num2 << endl;
        num1 = "";
        carry = 0;
        numExtraZero++;
    }

    if(isSign) {
        num2.insert(0,"-");
    }
    num2 = trim_leading_zeros(num2);

    return num2;
}
