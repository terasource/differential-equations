//
//  mathUtil.cpp
//  differential-equations
//
//  Created by Alp on 14.04.2026.
//
#include "mathUtil.hpp"
#include <math.h>
MathUtil::MathUtil(){}

double MathUtil::factorial(int x){
    double result = 1;
    while(x > 0)
        result *= x--;
    
    return result;
}
double MathUtil::pow(double base, int power){ // 5 3
    double result = 1;
    while(power > 0){
        if(power % 2 == 1) result *= base;
        base *= base;
        power /= 2;
    }
    
    return result;
}

/*
 implement exp and log functions using taylor series or different ways, but i want to rewrite them myself.
 for now it can stay as it is.
 */
double MathUtil::pow(double base, double power){
        return exp(power * log(base));
}



