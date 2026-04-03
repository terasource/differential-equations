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
    virtual Node* derivative() const = 0;
    virtual Node* clone() const = 0;
    virtual Node* simplifier() const {return clone();};
    
    virtual void print() const = 0;
};

class Constant : public Node {
    double value;
 public:
    Constant(double value);
    double evaluate(double x) const override;
    Node* derivative()const override;
    Node* clone() const override;
    void print() const override;
};

class Variable : public Node{
 public:
    double evaluate(double x) const override;
    Node* derivative()const override;
    Node* clone() const override;
    void print() const override;
};
class Sum : public Node{
private:
    Node* left;
    Node* right;
public:
    ~Sum();
    Sum(Node* l, Node* r);
    
    double evaluate(double x) const override;
    Node* derivative() const override;
    Node* clone() const override;
    Node* simplifier() const override;
    void print() const override;
};

class Subtract : public Node{
private:
    Node* left;
    Node* right;
public:
    ~Subtract();
    Subtract(Node* l, Node* r);
    double evaluate(double x) const override;
    Node* derivative() const override;
    Node* clone() const override;
    Node* simplifier() const override;
    void print() const override;
};

class Multiply : public Node{
 private:
    Node* left;
    Node* right;
 public:
    ~Multiply();
    Multiply(Node* l, Node* r);
    double evaluate(double x) const override;
    Node* derivative() const override;
    Node* clone() const override;
    Node* simplifier() const override;
    void print() const override;
};

class Divide : public Node{
 private:
    Node* left;
    Node* right;
 public:
    ~Divide();
    Divide(Node* l, Node* r);
    double evaluate(double x) const override;
    Node* derivative() const override;
    Node* clone() const override;
    Node* simplifier() const override;
    void print() const override;
};

class SinNode : public Node{
private:
    Node* child;
public:
    ~SinNode();
    SinNode(Node* child);
    double evaluate(double x) const override;
    Node* derivative()const override;
    Node* clone() const override;
    void print() const override;
};

class CosNode : public Node{
private:
    Node* child;
public:
    ~CosNode();
    CosNode(Node* child);
    double evaluate(double x) const override;
    Node* derivative()const override;
    Node* clone() const override;
    void print() const override;
};

class TanNode : public Node{
private:
    Node* child;
public:
    ~TanNode();
    TanNode(Node* child);
    double evaluate(double x) const override;
    Node* derivative()const override;
    Node* clone() const override;
    void print() const override;
};

class CotNode : public Node{
private:
    Node* child;
public:
    ~CotNode();
    CotNode(Node* child);
    double evaluate(double x) const override;
    Node* derivative()const override;
    Node* clone() const override;
    void print() const override;
};

