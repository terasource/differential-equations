//
//  node.cpp
//  differential-equations
//
//  Created by Alp on 9.03.2026.
//

#include "node.hpp"
#pragma once

Node::~Node(){}

Multiply::~Multiply(){delete left; delete right;}

SinNode::~SinNode() {}

CosNode::~CosNode() {}

//TanNode::~TanNode() {}

//CotNode::~CotNode() {}

Constant::Constant(double value) : value(value) {}

double Constant::evaluate(double x) const { return value; }

double Variable::evaluate(double x) const {return x; }

Multiply::Multiply(Node *l, Node* r) : left(l), right(r) {}

double Multiply::evaluate(double x) const { return left->evaluate(x) * right->evaluate(x); }

SinNode::SinNode(Node* c) : child(c) {}

double SinNode::evaluate(double x) const {
    
    return const_cast<function::Trigonometry::Sin&>(sin_obj)(x);
}

CosNode::CosNode(Node* c) : child(c) {}

double CosNode::evaluate(double x) const {
    /*
     double inner_value = child->evaluate(x);
     
     double radians = inner_value * (M_PI / 180.0);
     */
    
    return const_cast<function::Trigonometry::Cos&>(cos_obj)(x);
}

/*
TanNode::TanNode(Node* c) : child(c), tan_obj( {}

double TanNode::evaluate(double x) const {
    
    return const_cast<function::Trigonometry::Tan&>(tan_obj)(x);
}

double CotNode::evaluate(double x) const {
    
    return const_cast<function::Trigonometry::Cot&>(cot_obj)(x);
}
*/
