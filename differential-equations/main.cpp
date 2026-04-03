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
// we need a simplifier function in order to get rid of the long arithmatic derivative expression (done)

// and also now with the help of the expression tree we are no longer need to operator of function.hpp and .cpp because
// we just can calculate the nodes(functions) with the evaluate function that is inside in nodes. so we need to modify
// function.hpp file as an helper class not a class we create a object from in order to prevent the identify conflicts

// refactor raw pointers to shared_ptr for better memory management on nodes
// implement a pow function
// implement a symbolic and numerical integral methods

int main(int argc, const char * argv[]) {
    
    std::map<double, int> test_f = {{1.0, 2},{2.0,2}}; // we assume that f(x) = 2x + 2x^2 and for x = 2 f(2) = 12
    std::map<double, int> test_f2 = {{1.0,2} , {2.0, 1}};
    // and if we assume f(x) = 2x + x^2 f(2) should be 8.
    function ftf(test_f);
    function ftf2(test_f2);
    function f({{2.0, 1}});  // we can initialize the function with this way too
    function::Derivative df(ftf);
    
    Node* fn = new Multiply(new Constant(5.0), new Variable());
    Node* dfn = fn->derivative();
    Node* dfns = dfn->simplifier();
    
    std::cout << "Raw Function = "; fn->print(); std::cout << std::endl;
    std::cout << "Derivative of the function = "; dfn->print(); std::cout << std::endl;
    std::cout << "Simplified version of the Derivated function = "; dfns->print(); std::cout << std::endl;
    std::cout << fn->evaluate(2) << std::endl;
    
    delete dfn;
    return 0;
}
