//
//  function.hpp
//  differential-equations
//
//  Created by Alp on 5.03.2026.
//
#pragma once
#include <iostream>
#include <map>
#include <functional>


class function{
private:
    std::map<double, int> coefficients;
    double power;
    double value = 0;
    std::function<double(double)> evaluator;
    
public:
    function();
    function(std::map<double, int> coefficients);
    function(std::function<double(double)> evaluator);
    double f(double x);
    double derivative();
    double operator()(double x);
    
    class Derivative {
    public:
        Derivative(function &f);
        function& parent;
        double operator()(double x);
    private:
    };
    
    class Trigonometry {
    public:
        static double sin(double x);
        static double cos(double x);
        static double tan(double x);
        static double cot(double x);
        
    };
    
};
