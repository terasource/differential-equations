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

double factorial(int x){
    double result = 1;
    while(x > 0)
        result *= x--;
    
    return result;
}

function::function(){
    this->coefficients = {{0.0,0}};
}

function::function(std::map<double, int> coefficients){
    this->coefficients = coefficients;
}
function::function(std::function<double(double)> evaluator){
    this->evaluator = evaluator;
}

function::Derivative::Derivative(function &f) : parent(f){}

function::Trigonometry::Trigonometry(function &f) : parent(f) {}

function::Trigonometry::Sin::Sin() {}

function::Trigonometry::Cos::Cos() {}

function::Trigonometry::Tan::Tan(Trigonometry &t) : t_parent(t) {}

function::Trigonometry::Cot::Cot(Trigonometry &t) : t_parent(t) {}

double function::f(double x){
    this->value = 0;
    
        for(auto c : coefficients)
            value += c.second * pow(x, c.first);
        
        return value;
    
}

double function::operator()(double x){
    if(evaluator)
    return this->evaluator(x);
    
        return function::f(x);
}


double function::Derivative::operator()(double x){
    const double h = 1e-7;
    
    return (parent(x+h) - parent(x-h)) / (2.0 * h);
}

double function::Trigonometry::Sin::operator()(double x){
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

double function::Trigonometry::Cos::operator()(double x){
    const int n = 3;
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

double function::Trigonometry::Tan::operator()(double x){
    double sin = t_parent.sin(x);
    double cos = t_parent.cos(x);
    
    if(std::abs(cos) < 1e-16){
        return INFINITY;
    }
    
    return sin/cos;
}

double function::Trigonometry::Cot::operator()(double x){
    
    double sin = t_parent.sin(x);
    double cos = t_parent.cos(x);
    
    if(std::abs(sin) < 1e-16){
        return INFINITY;
    }
    
    return cos/sin;
}
