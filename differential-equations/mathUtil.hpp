//
//  mathutil.hpp
//  differential-equations
//
//  Created by Alp on 14.04.2026.
//
#pragma once

class MathUtil{
private:
    MathUtil();
public:
    static double pow(double base, int power);
    static double pow(double base, double power);
    static double factorial(int x);
};
