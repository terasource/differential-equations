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

Subtract::Subtract(Node* l, Node* r) : left(l), right(r) {}

double Subtract::evaluate(double x) const { return left->evaluate(x) - right->evaluate(x);}
// (Q2) in the term of the math, I could just multiply the right root with -1 in the Summition derivate Node in order to
// get the operation of the substraction derivative? could not i?
Node* Subtract::derivative() const {return new Subtract(left->derivative(), right->derivative());}
Node* Subtract::clone() const {return new Subtract(left->clone(), right->clone());}

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

