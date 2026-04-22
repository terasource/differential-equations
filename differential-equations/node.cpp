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
#include "mathUtil.hpp"

using smartNode = std::shared_ptr<Node>;

Node::~Node(){}

Sum::~Sum(){}

Subtract::~Subtract(){}

Multiply::~Multiply(){}

Divide::~Divide() {}

SinNode::~SinNode() {}

CosNode::~CosNode() {}

TanNode::~TanNode() {}

CotNode::~CotNode() {}

PowerNode::~PowerNode() {}

Constant::Constant(double value) : value(value) {}

double Constant::evaluate(double x) const { return value; }
smartNode Constant::derivative() const {return std::make_shared<Constant>(0.0); }
smartNode Constant::clone() const {return std::make_shared<Constant>(value);}
void Constant::print() const {std::cout << value;}

double Variable::evaluate(double x) const {return x; }
smartNode Variable::derivative() const {return std::make_shared<Constant>(1.0); }
smartNode Variable::clone() const {return std::make_shared<Variable>(); }
void Variable::print() const {std::cout << "x";};

Sum::Sum(smartNode l, smartNode r) : left(l), right(r) {}

void Sum::print() const {std::cout << "("; left->print(); std::cout << " + "; right->print(); std::cout << ")"; }

double Sum::evaluate(double x) const { return left->evaluate(x) + right->evaluate(x);}

smartNode Sum::derivative() const {
    smartNode result = std::make_shared<Sum>(left->derivative(), right->derivative());
    return result->simplifier();
}

smartNode Sum::clone() const {return std::make_shared<Sum>(left->clone(), right->clone());}

smartNode Sum::simplifier() const {
    //rules
    //A+B = C
    //A+0 = A
    //0+A = A
    
    smartNode sleft = left->simplifier();
    smartNode sright = right->simplifier();
    
    std::shared_ptr<Constant> lconst = std::dynamic_pointer_cast<Constant>(sleft);
    std::shared_ptr<Constant> rconst = std::dynamic_pointer_cast<Constant>(sright);

    if(lconst && lconst->evaluate(0) == 0){
        return sright;
    }
    if(rconst && rconst->evaluate(0) == 0){
        return sleft;
    }
    if(lconst && rconst){
        double val = sleft->evaluate(1) + sright->evaluate(1);
        return std::make_shared<Constant>(val);
    }

    return std::make_shared<Sum>(sleft, sright);
}

Subtract::Subtract(smartNode l, smartNode r) : left(l), right(r) {}

double Subtract::evaluate(double x) const { return left->evaluate(x) - right->evaluate(x);}
// (Q2) in the term of the math, I could just multiply the right root with -1 in the Summition derivate Node in order to
// get the operation of the substraction derivative? could not i?
smartNode Subtract::derivative() const {
    smartNode result = std::make_shared<Subtract>(left->derivative(), right->derivative());
    return result->simplifier();
}
smartNode Subtract::clone() const {return std::make_shared<Subtract>(left->clone(), right->clone());}

smartNode Subtract::simplifier() const {
    //rules
    //A-B = C
    //A-0 = A
    //0-A = -A
    
    smartNode sleft = left->simplifier();
    smartNode sright = right->simplifier();
    
    std::shared_ptr<Constant> lconst = std::dynamic_pointer_cast<Constant>(sleft);
    std::shared_ptr<Constant> rconst = std::dynamic_pointer_cast<Constant>(sright);
    
    if(lconst && lconst->evaluate(0) == 0){
        if(rconst){
            double value =  -1 * sright->evaluate(0);
            return std::make_shared<Constant>(value);
        }else
            return std::make_shared<Multiply>(std::make_shared<Constant>(-1.0), sright);
    }

    if(rconst && rconst->evaluate(0) == 0){
        return sleft;
    }
    
    if(lconst && rconst){
        double val = sleft->evaluate(0) -sright->evaluate(0);
        
        
        return std::make_shared<Constant>(val);
        
    }
    return  std::make_shared<Subtract>(sleft, sright);
}

void Subtract::print() const {std::cout << "("; left->print(); std::cout << " - "; right->print(); std::cout << ")";}

Multiply::Multiply(smartNode l, smartNode r) : left(l), right(r) {}

double Multiply::evaluate(double x) const { return left->evaluate(x) * right->evaluate(x); }

smartNode Multiply::derivative() const {
    smartNode result = std::make_shared<Sum>(
                   std::make_shared<Multiply>(left->derivative(), right->clone()),
                   std::make_shared<Multiply>(left->clone(), right->derivative())
                   );
    
    return result->simplifier();
}
smartNode Multiply::clone() const {return std::make_shared<Multiply>(left->clone(), right->clone());}

smartNode Multiply::simplifier() const {

    smartNode sleft = left->simplifier();
    smartNode sright = right->simplifier();
    
    std::shared_ptr<Constant> lconst = std::dynamic_pointer_cast<Constant>(sleft);
    std::shared_ptr<Constant> rconst = std::dynamic_pointer_cast<Constant>(sright);
    
    if(lconst && lconst->evaluate(0) == 0){
        return std::make_shared<Constant>(0.0);
    }
    
    if(rconst && rconst->evaluate(0) == 0){
        return std::make_shared<Constant>(0.0);
    }
    
    if(lconst && lconst->evaluate(0) == 1){
        return sright;
    }
    if(rconst && rconst->evaluate(0) == 1){
        return sleft;
    }
    
    
    if(lconst != nullptr && rconst != nullptr){
        double val = lconst->evaluate(0) * rconst->evaluate(0);
        return std::make_shared<Constant>(val);
    }
        
    
    return std::make_shared<Multiply>(sleft, sright);
}
void Multiply::print() const {std::cout << "("; left->print(); std::cout << " * "; right->print(); std::cout << ")"; }

Divide::Divide(smartNode l, smartNode r) : left(l), right(r) {}

double Divide::evaluate(double x) const { return left->evaluate(x) / right->evaluate(x); }

smartNode Divide::derivative() const {
    smartNode result = std::make_shared<Divide>(std::make_shared<Subtract>(std::make_shared<Multiply>(left->derivative(), right->clone()),
        std::make_shared<Multiply>(left->clone(), right->derivative())
        ),
        std::make_shared<Multiply>(right->clone(), right->clone())
        );
    return result->simplifier();
}
smartNode Divide::clone() const {return std::make_shared<Divide>(left->clone(), right->clone()); }
smartNode Divide::simplifier() const {
    //rules
    // A/1 = A;
    // 1/A = 1/A;
    // A/0 = undefined;
    // 0/A = 0;
    // A/B = C;
    
    smartNode sleft = left->simplifier();
    smartNode sright = right->simplifier();
    
    std::shared_ptr<Constant> lconst = std::dynamic_pointer_cast<Constant>(sleft);
    std::shared_ptr<Constant> rconst = std::dynamic_pointer_cast<Constant>(sright);
    
    if(rconst && rconst->evaluate(0) == 1){
        return sleft;
    }
    if(lconst && lconst->evaluate(0) == 1){
        return std::make_shared<Divide>(sleft,sright);
    }
    if(lconst && lconst->evaluate(0) == 0){
        return std::make_shared<Constant>(0);
    }
    if(rconst && rconst->evaluate(0) == 0){
        throw std::runtime_error("Divison by zero! ");
    }
    if(lconst && rconst){
        double lval = sleft->evaluate(0);
        double rval = sright->evaluate(0);
        double val = lval / rval;
        return std::make_shared<Constant>(val);
    }
    
    return std::make_shared<Divide>(sleft, sright);
}

void Divide::print() const {std::cout << "("; left->print(); std::cout << " / "; right->print(); std::cout << ")"; }

SinNode::SinNode(smartNode c) : child(c) {}

double SinNode::evaluate(double x) const {
    double val = child->evaluate(x);
    return function::Trigonometry::sin(val);
}
smartNode SinNode::derivative() const {
    return std::make_shared<Multiply>(child->derivative(), std::make_shared< CosNode>(child->clone()));
}

smartNode SinNode::clone() const {return std::make_shared<SinNode>(child->clone());}
void SinNode::print() const {std::cout << "sin("; child->print(); std::cout << ")";}

CosNode::CosNode(smartNode c) : child(c) {}

double CosNode::evaluate(double x) const {
    double val = child->evaluate(x);
    return function::Trigonometry::cos(val);
}

smartNode CosNode::derivative() const { return std::make_shared<Multiply>(child->derivative(), std::make_shared<Multiply>(std::make_shared<Constant>(-1.0), std::make_shared<SinNode>(child->clone())));}

smartNode CosNode::clone() const {return std::make_shared<CosNode>(child->clone());}

void CosNode::print() const {std::cout << "cos("; child->print(); std::cout << ")";}

TanNode::TanNode(smartNode c) : child(c) {}

double TanNode::evaluate(double x) const {
    double val = child->evaluate(x);
    return function::Trigonometry::tan(val);
}
smartNode TanNode::derivative() const {
    std::shared_ptr<Divide> nD = std::make_shared<Divide>(std::make_shared<SinNode>(child->clone()), std::make_shared<CosNode>(child->clone()));
    smartNode result = nD->derivative();
    return result;
}

smartNode TanNode::clone() const {return std::make_shared<TanNode>(child->clone());}
void TanNode::print() const {std::cout << "tan("; child->print(); std::cout << ")";}

CotNode::CotNode(smartNode c) : child(c){}

double CotNode::evaluate(double x) const {
    double val = child->evaluate(x);
    return function::Trigonometry::cot(val);
}

smartNode CotNode::derivative() const {
    std::shared_ptr<Divide> nD = std::make_shared<Divide>(std::make_shared<CosNode>(child->clone()), std::make_shared<SinNode>(child->clone()));
    smartNode result = nD->derivative();
    return result;
}

smartNode CotNode::clone() const {return std::make_shared<CotNode>(child->clone());}

void CotNode::print() const {std::cout << "cot("; child->print(); std::cout << ")";}

PowerNode::PowerNode(smartNode base, smartNode exponent) : base(base), exponent(exponent) {}

double PowerNode::evaluate(double x) const {
    return MathUtil::pow(base->evaluate(x), exponent->evaluate(x));
}

smartNode PowerNode::clone() const {
    return std::make_shared<PowerNode>(base->clone(), exponent->clone());
}

smartNode PowerNode::derivative() const {
    std::shared_ptr<Constant> exponent_constant = std::dynamic_pointer_cast<Constant>(exponent);
    std::shared_ptr<Variable> exponent_variable = std::dynamic_pointer_cast<Variable>(exponent);
    std::shared_ptr<Constant> base_constant = std::dynamic_pointer_cast<Constant>(base);
    std::shared_ptr<Variable> base_variable = std::dynamic_pointer_cast<Variable>(base);
    
    if(base_constant && exponent_constant)
        return std::make_shared<Constant>(0);

    if(base_constant && exponent_variable){
        smartNode result = std::make_shared<Constant>(log(base->evaluate(0))) * this->clone() * exponent->derivative();
        return result->simplifier();
    }
    
    if(base_variable && exponent_constant){
        smartNode result = std::make_shared<Constant>(exponent->evaluate(0)) * std::make_shared<PowerNode>(base, std::make_shared<Constant>(exponent->evaluate(0) - 1)) * base->derivative();
        
        return result->simplifier();
    }
    
    if(base_variable && exponent_variable)
        throw std::runtime_error("x^x derivative not implemented");

    return std::make_shared<Multiply>(base, exponent);
}

smartNode PowerNode::simplifier() const{
    std::shared_ptr<Constant> exponent_constant = std::dynamic_pointer_cast<Constant>(exponent);
    std::shared_ptr<Constant> base_constant = std::dynamic_pointer_cast<Constant>(base);
    
    if(base_constant && base_constant->evaluate(0) == 1)
        return std::make_shared<Constant>(1);
    if(base_constant && base_constant->evaluate(0) == 0)
        return std::make_shared<Constant>(0);
    if(exponent_constant && exponent_constant->evaluate(0) == 1)
        return base;
    if(exponent_constant && exponent_constant->evaluate(0) == 0)
        return std::make_shared<Constant>(1);
    
    return this->clone();
}

void PowerNode::print() const {
    base->print(); std::cout << "^"; exponent->print();
}
