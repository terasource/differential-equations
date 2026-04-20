//
//  node.hpp
//  differential-equations
//
//  Created by Alp on 9.03.2026.
//
#pragma once
#include "function.hpp"
class Node;

using smartNode = std::shared_ptr<Node>;

class Node{
 public:
    virtual ~Node();
    virtual double evaluate(double x) const = 0;
    virtual smartNode derivative() const = 0;
    virtual smartNode clone() const = 0;
    virtual smartNode simplifier() const {return clone();};
    
    virtual void print() const = 0;
};

class Constant : public Node {
    double value;
 public:
    Constant(double value);
    double evaluate(double x) const override;
    smartNode derivative()const override;
    smartNode clone() const override;
    void print() const override;
};

class Variable : public Node{
 public:
    double evaluate(double x) const override;
    smartNode derivative()const override;
    smartNode clone() const override;
    void print() const override;
};
class Sum : public Node{
private:
    smartNode left;
    smartNode right;
public:
    ~Sum();
    Sum(smartNode l, smartNode r);
    
    double evaluate(double x) const override;
    smartNode derivative() const override;
    smartNode clone() const override;
    smartNode simplifier() const override;
    void print() const override;
    
};

class Subtract : public Node{
private:
    smartNode left;
    smartNode right;
public:
    ~Subtract();
    Subtract(smartNode l, smartNode r);
    double evaluate(double x) const override;
    smartNode derivative() const override;
    smartNode clone() const override;
    smartNode simplifier() const override;
    void print() const override;
};

class Multiply : public Node{
 private:
    smartNode left;
    smartNode right;
 public:
    ~Multiply();
    Multiply(smartNode l, smartNode r);
    double evaluate(double x) const override;
    smartNode derivative() const override;
    smartNode clone() const override;
    smartNode simplifier() const override;
    void print() const override;
};

class Divide : public Node{
 private:
    smartNode left;
    smartNode right;
 public:
    ~Divide();
    Divide(smartNode l, smartNode r);
    double evaluate(double x) const override;
    smartNode derivative() const override;
    smartNode clone() const override;
    smartNode simplifier() const override;
    void print() const override;
};

inline smartNode operator+(smartNode l, smartNode r) {return std::make_shared<Sum>(l,r);}
inline smartNode operator-(smartNode l, smartNode r) {return std::make_shared<Subtract>(l,r);}
inline smartNode operator*(smartNode l, smartNode r) {return std::make_shared<Multiply>(l,r);}
inline smartNode operator/(smartNode l, smartNode r) {return std::make_shared<Divide>(l,r);}
    
class SinNode : public Node{
private:
    smartNode child;
public:
    ~SinNode();
    SinNode(smartNode child);
    double evaluate(double x) const override;
    smartNode derivative()const override;
    smartNode clone() const override;
    void print() const override;
};

class CosNode : public Node{
private:
    smartNode child;
public:
    ~CosNode();
    CosNode(smartNode child);
    double evaluate(double x) const override;
    smartNode derivative()const override;
    smartNode clone() const override;
    void print() const override;
};

class TanNode : public Node{
private:
    smartNode child;
public:
    ~TanNode();
    TanNode(smartNode child);
    double evaluate(double x) const override;
    smartNode derivative()const override;
    smartNode clone() const override;
    void print() const override;
};

class CotNode : public Node{
private:
    smartNode child;
public:
    ~CotNode();
    CotNode(smartNode child);
    double evaluate(double x) const override;
    smartNode derivative()const override;
    smartNode clone() const override;
    void print() const override;
};

