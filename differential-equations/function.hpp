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
        
        class Sin{
        public:
            Sin();
            double operator()(double x);
        };
        
        class Cos{
        public:
            Cos();
            double operator()(double x);
        };
        
        class Tan{
        public:
            Tan(Trigonometry &t);
            double operator()(double x);
        private:
            Trigonometry& t_parent;
        };
        
        class Cot{
        public:
            Cot(Trigonometry &t);
            double operator()(double x);
        private:
            Trigonometry& t_parent;
        };

        Trigonometry(function &f);
        function& parent;
        Sin sin;
        Cos cos;
        double operator()(double x);
    };
    
};
