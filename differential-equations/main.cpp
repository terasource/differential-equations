//
//  main.cpp
//  differential-equations
//
//  Created by Alp on 5.03.2026.
//
#include <iostream>
#include "function.hpp"
#include <map>
#include "node.hpp"

#define degree M_PI / 180
// TO-DO
// create a base virtual class and its sub classes that inherites base
// create a sub classes for every different kind of functions like trigonometric functions, logaritmic functions
// create a derivate function and expression to get the derrivative of function with df(x)
// check the std::function and merge the polynomial functions calculations that i created with map with other kind of functions in it.
//

int main(int argc, const char * argv[]) {
    
    std::map<double, int> test_f = {{2.0,1}}; // we assume that f(x) = 2x + 2x^2 and for x = 2 f(2) = 12
    // and if we assume f(x) = 2x + x^2 f(2) should be 8.
    
    function f({{2.0, 1}});  // we can initialize the function with this way too
    function::Derivative df(f);
    function::Trigonometry t(f);
    function::Trigonometry::Sin sin;
    function::Trigonometry::Cos cos;
    function::Trigonometry::Tan tan(t);
    function::Trigonometry::Cot cot(t);
    
   /*
    function sin([](double x){
        return std::sin(x);
    });
    */
    
    /*
    std::cout << f(2) << std::endl;
    std::cout << df(1) << std::endl;
    std::cout << sin(degree * 90) << std::endl;
    std::cout << tan(degree * 45) << std::endl;
    std::cout << cot(degree * 0) << std::endl;
    */
    std::cout << cos(30) << std::endl;
    
    Node* expr = new Multiply(new Constant(5.0),new Variable());
    Node* expr2 = new Multiply(new Variable(), new SinNode(new Constant(90)));
    Node* expr3 = new Multiply(new Variable(), new CosNode(new Constant(0)));
    
    double res = expr->evaluate(2.0);
    
    std::cout << "f(x) = 5x and f(2) = " << res << std::endl;
   
    double res2 = expr2->evaluate(5);
    
    std::cout << "x * sin(90) for x = 5 is equal to = " << res2 << std::endl;

    double res3 = expr3->evaluate(1);
    
    std::cout << "x * cos(90) for x = 10 is equal to = " << res3 << std::endl;

    
    return 0;
}
