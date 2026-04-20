//
//  function.cpp
//  differential-equations
//
//  Created by Alp on 5.03.2026.
//

#include "function.hpp"
#include <iostream>
#include <map>
#include <cmath>
#include "mathUtil.hpp"


double function::Trigonometry::sin(double x){
    const int n = 16;
    double result = 0;
    
    x = fmod(x, 360);
    if(x < 0) x += 360;
    
    if(x == 0.0 || x == 360.0 || x == 180.0) return 0.0;
    if(x == 90.0) return 1.0;
    if(x == 270.0) return -1.0;
    
    x *= M_PI / 180;
    double prev_term = x;
    for(int i = 1; i < n; i++){
        result += prev_term;
        prev_term *= -1 * pow(x, 2) / ((2 * i ) * (2 * i + 1));
    }
    
    return result;
}

double function::Trigonometry::cos(double x){
    const int n = 16;
    double result = 0;
    
    x = fmod(x, 360);
    if(x < 0) x += 360;
    
    if(x == 0.0 || x == 360.0) return 1.0;
    if(x == 90.0 || x == 270.0) return 0.0;
    if(x == 180.0) return -1.0;
   
    x *= M_PI / 180;
    double prev_term = 1;
    
    for(int i = 1; i < n; i++){
        result += prev_term;
        prev_term *= -1 * pow(x, 2) / ((2 * i) * (2 * i - 1));
    }
    
    return result;
}

double function::Trigonometry::tan(double x){
    double sin = function::Trigonometry::sin(x);
    double cos = function::Trigonometry::cos(x);
    
    if(std::abs(cos) < 1e-16){
        return INFINITY;
    }
    
    return sin/cos;
}

double function::Trigonometry::cot(double x){
    double sin = function::Trigonometry::sin(x);
    double cos = function::Trigonometry::cos(x);
    
    if(std::abs(sin) < 1e-16){
        return INFINITY;
    }
    
    return cos/sin;
}
