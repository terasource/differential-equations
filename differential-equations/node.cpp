//
//  node.cpp
//  differential-equations
//
//  Created by Alp on 9.03.2026.
//
//-----------------------------------------------------------------------------------------------------------
//16/03/2026 to-do
//add the derivative rules for every class that overrides Node class
//implement a simplifier in order to prevent the flaws during the derivation like 5x = (0 * x) + (5 * 1)
//try to visualize the nodes in console.
//-----------------------------------------------------------------------------------------------------------

#include "node.hpp"
#include <iostream>
#pragma once

Node::~Node(){}

Sum::~Sum(){delete left; delete right;}

Subtract::~Subtract(){delete left; delete right;}

Multiply::~Multiply(){delete left; delete right;}

Divide::~Divide() {delete left; delete right;}

SinNode::~SinNode() {delete child;}

CosNode::~CosNode() {delete child;}

TanNode::~TanNode() {delete child;}

CotNode::~CotNode() {delete child;}

Constant::Constant(double value) : value(value) {}

double Constant::evaluate(double x) const { return value; }
Node* Constant::derivative() const {return new Constant(0.0); }
Node* Constant::clone() const {return new Constant(value);}
void Constant::print() const {std::cout << value;}

double Variable::evaluate(double x) const {return x; }
Node* Variable::derivative() const {return new Constant(1.0); }
Node* Variable::clone() const {return new Variable(); }
void Variable::print() const {std::cout << "x";};

Sum::Sum(Node* l, Node* r) : left(l), right(r) {}

void Sum::print() const {std::cout << "("; left->print(); std::cout << " + "; right->print(); std::cout << ")"; }

double Sum::evaluate(double x) const { return left->evaluate(x) + right->evaluate(x);}
Node* Sum::derivative() const {return new Sum(left->derivative(), right->derivative());}
Node* Sum::clone() const {return new Sum(left->clone(), right->clone());}

Node* Sum::simplifier() const {
    //rules
    //A+B = C
    //A+0 = A
    //0+A = A
    
    Node* sleft = left->simplifier();
    Node* sright = right->simplifier();
    
    Constant* lconst = dynamic_cast<Constant*>(sleft);
    Constant* rconst = dynamic_cast<Constant*>(sright);
    
    if(lconst && lconst->evaluate(0) == 0){
        delete sleft;
        return sright;
    }
    if(rconst && rconst->evaluate(0) == 0){
        delete sright;
        return sleft;
    }
    if(lconst && rconst){
        double val = sleft->evaluate(1) + sright->evaluate(1);
        delete sleft; delete sright;
        return new Constant(val);
    }

    return new Sum(sleft, sright);
}

Subtract::Subtract(Node* l, Node* r) : left(l), right(r) {}

double Subtract::evaluate(double x) const { return left->evaluate(x) - right->evaluate(x);}
// (Q2) in the term of the math, I could just multiply the right root with -1 in the Summition derivate Node in order to
// get the operation of the substraction derivative? could not i?
Node* Subtract::derivative() const {return new Subtract(left->derivative(), right->derivative());}
Node* Subtract::clone() const {return new Subtract(left->clone(), right->clone());}

Node* Subtract::simplifier() const {
    //rules
    //A-B = C
    //A-0 = A
    //0-A = -A
    
    Node* sleft = left->simplifier();
    Node* sright = right->simplifier();
    
    Constant* lconst = dynamic_cast<Constant*>(sleft);
    Constant* rconst = dynamic_cast<Constant*>(sright);
    
    if(lconst && lconst->evaluate(0) == 0){
        delete sleft;
        if(rconst){
            double value =  -1 * sright->evaluate(0);
            delete sright;
            return new Constant(value);
        }else
            return new Multiply(new Constant(-1.0), sright);
    }

    if(rconst && rconst->evaluate(0) == 0){
        delete sright;
        return sleft;
    }
    
    if(lconst && rconst){
        double val = sleft->evaluate(0) -sright->evaluate(0);
        
        delete sleft; delete sright;
        
        return new Constant(val);
    }

    return new Subtract(sleft, sright);
}

void Subtract::print() const {std::cout << "("; left->print(); std::cout << " - "; right->print(); std::cout << ")";}

Multiply::Multiply(Node *l, Node* r) : left(l), right(r) {}

double Multiply::evaluate(double x) const { return left->evaluate(x) * right->evaluate(x); }

Node* Multiply::derivative() const {
    return new Sum(
                   new Multiply(left->derivative(), right->clone()),
                   new Multiply(left->clone(), right->derivative())
                   );
}
Node* Multiply::clone() const {return new Multiply(left->clone(), right->clone());}

Node* Multiply::simplifier() const {

    Node* sleft = left->simplifier();
    Node* sright = right->simplifier();
    
    Constant* lconst = dynamic_cast<Constant*>(sleft);
    Constant* rconst = dynamic_cast<Constant*>(sright);
    
    if(lconst && lconst->evaluate(0) == 0){
        delete sleft; delete sright;
        return new Constant(0.0);
    }
    
    if(rconst && rconst->evaluate(0) == 0){
        delete sleft; delete sright;
        return new Constant(0.0);
    }
    
    if(lconst && lconst->evaluate(0) == 1){
        delete sleft;
        return sright;
    }
    if(rconst && rconst->evaluate(0) == 1){
        delete sright;
        return sleft;
    }
    
    
    if(lconst != nullptr && rconst != nullptr){
        double val = lconst->evaluate(0) * rconst->evaluate(0);
        delete sleft; delete sright;
        return new Constant(val);
    }
        
    
    return new Multiply(sleft, sright);
}
void Multiply::print() const {std::cout << "("; left->print(); std::cout << " * "; right->print(); std::cout << ")"; }

Divide::Divide(Node* l, Node *r) : left(l), right(r) {}

double Divide::evaluate(double x) const { return left->evaluate(x) / right->evaluate(x); }

Node* Divide::derivative() const {
    return new Divide(new Subtract(new Multiply(left->derivative(), right->clone()),
                                   new Multiply(left->clone(), right->derivative())
                                   ),
                      new Multiply(right->clone(), right->clone())
                      );
}
Node* Divide::clone() const {return new Divide(left->clone(), right->clone()); }
Node* Divide::simplifier() const {
    //rules
    // A/1 = A;
    // 1/A = 1/A;
    // A/0 = undefined;
    // 0/A = 0;
    // A/B = C;
    
    Node* sleft = left->simplifier();
    Node* sright = right->simplifier();
    
    Constant* lconst = dynamic_cast<Constant*>(sleft);
    Constant* rconst = dynamic_cast<Constant*>(sright);
    
    if(rconst && rconst->evaluate(0) == 1){
        delete sright;
        return sleft;
    }
    if(lconst && lconst->evaluate(0) == 1){
        return new Divide(sleft,sright);
    }
    if(lconst && lconst->evaluate(0) == 0){
        delete sleft; delete sright;
        return new Constant(0);
    }
    if(rconst && rconst->evaluate(0) == 0){
        delete sright;
        delete sleft;
        throw std::runtime_error("Divison by zero! ");
    }
    if(lconst && rconst){
        double lval = sleft->evaluate(0);
        double rval = sright->evaluate(0);
        double val = lval / rval;
        delete sleft; delete sright;
        return new Constant(val);
    }
    
    return new Divide(sleft, sright);
}

void Divide::print() const {std::cout << "("; left->print(); std::cout << " / "; right->print(); std::cout << ")"; }

SinNode::SinNode(Node* c) : child(c) {}

double SinNode::evaluate(double x) const {
    double val = child->evaluate(x);
    return function::Trigonometry::sin(val);
}
Node* SinNode::derivative() const {return new Multiply(child->derivative(), new CosNode(child->clone()));}

Node* SinNode::clone() const {return new SinNode(child->clone());}
void SinNode::print() const {std::cout << "sin("; child->print(); std::cout << ")";}

CosNode::CosNode(Node* c) : child(c) {}

double CosNode::evaluate(double x) const {
    double val = child->evaluate(x);
    return function::Trigonometry::cos(val);
}

Node* CosNode::derivative() const { return new Multiply(child->derivative(), new Multiply(new Constant(-1.0), new SinNode(child->clone())));}

Node* CosNode::clone() const {return new CosNode(child->clone());}

void CosNode::print() const {std::cout << "cos("; child->print(); std::cout << ")";}

TanNode::TanNode(Node* c) : child(c) {}

double TanNode::evaluate(double x) const {
    double val = child->evaluate(x);
    return function::Trigonometry::tan(val);
}
Node* TanNode::derivative() const {
    Divide* nD = new Divide(new SinNode(child->clone()), new CosNode(child->clone()));
    Node* result = nD->derivative();
    delete nD;
    return result;
}

Node* TanNode::clone() const {return new TanNode(child->clone());}
void TanNode::print() const {std::cout << "tan("; child->print(); std::cout << ")";}

CotNode::CotNode(Node* c) : child(c){}

double CotNode::evaluate(double x) const {
    double val = child->evaluate(x);
    return function::Trigonometry::cot(val);
}

Node* CotNode::derivative() const {
    Divide* nD = new Divide(new CosNode(child->clone()), new SinNode(child->clone()));
    Node* result = nD->derivative();
    delete nD;
    return result;
}

Node* CotNode::clone() const {return new CotNode(child->clone());}

void CotNode::print() const {std::cout << "cot("; child->print(); std::cout << ")";}

