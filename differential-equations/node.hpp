//
//  node.hpp
//  differential-equations
//
//  Created by Alp on 9.03.2026.
//

#include "function.hpp"

class Node{
 public:
    virtual ~Node();
    virtual double evaluate(double x) const = 0;
    
};

class Constant : public Node {
    double value;
 public:
    Constant(double value);
    double evaluate(double x) const override;
};

class Variable : public Node{
 public:
    double evaluate(double x) const override;
};

class Multiply : public Node{
 private:
    Node* left;
    Node* right;
 public:
    ~Multiply();
    Multiply(Node* l, Node* r);
    double evaluate(double x) const override;
};

class SinNode : public Node{
private:
    function::Trigonometry::Sin sin_obj;
    Node* child;
public:
    ~SinNode();
    SinNode(Node* child);
    double evaluate(double x) const override;
};

class CosNode : public Node{
private:
    function::Trigonometry::Cos cos_obj;
    Node* child;
public:
    ~CosNode();
    CosNode(Node* child);
    double evaluate(double x) const override;
};
/*
class TanNode : public Node{
private:
    function::Trigonometry::Tan tan_obj;
    Node* child;
public:
    ~TanNode();
    TanNode(Node* child);
    double evaluate(double x) const override;
};

class CotNode : public Node{
private:
    function::Trigonometry::Cot cot_obj;
    Node* child;
public:
    ~CotNode();
    CotNode(Node* child);
    double evaluate(double x) const override;
};
*/
