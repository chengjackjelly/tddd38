/*
  Implement the classes:
  - Node
  - Number
  - Operator
  - Addition
  - Subtraction
  - Multiplication
  - Division

  Node should have the following (pure virtual) members:
  - double evaluate()
    + Calculate the expression stored in 'this'
  - void print(std::ostream& os)
    + print the expression represented in 'this'
  - void print_tree(std::ostream& os, int depth)
    + print a textual representation of the expression tree
  - Node* clone()
    + return a a new instance of the expression stored in 'this'
 */
#include <iostream>
using std::ostream;
class Node
{
public:
  Node()
  {
    std::cout << "test node constructor" << std::endl;
  }
  virtual ~Node() = default;
  virtual double evaluate() { return 0.0; };
  virtual void print_tree(ostream &, int){};
  virtual Node *expand(){};
  virtual Node *clone()
  {
    return new Node();
  };
  virtual void print(ostream &os){};
};
class Number : public Node
{
public:
  Number(double v);
  double evaluate() override;
  void print_tree(ostream &, int) override;
  Node *clone() override;
  void print(std::ostream &os) override;
  Node *expand() override;

private:
  double value;
};
class Operator : public Node
{
public:
  Operator(Node *, Node *);
  // double evaluate() override;
  // void print_tree(ostream &, int) override;
  Node *clone() override { return new Node(); };
  ~Operator();
  Node *expand() override;
  static Node *left_expand(Operator *);
  static Node *right_expand(Operator *);

protected:
  Node *left;
  Node *right;
};
class Addition : public Operator
{
public:
  Addition(Node *l, Node *r) : Operator(l, r) {}

protected:
  double evaluate() override;
  void print_tree(ostream &, int) override;
  Node *clone() override;
  void print(std::ostream &os) override;
};
class Subtraction : public Addition
{
public:
  Subtraction(Node *l, Node *r) : Addition(l, r) {}

  double evaluate() override;
  void print_tree(ostream &, int) override;
  Node *clone() override;
};
class Multiplication : public Operator
{
public:
  Multiplication(Node *l, Node *r) : Operator(l, r) {}

protected:
  double evaluate() override;
  void print_tree(ostream &, int) override;
  Node *clone() override;
  void print(ostream &os) override;
};
class Division : public Multiplication
{
public:
  Division(Node *l, Node *r) : Multiplication(l, r) {}

protected:
  double evaluate() override;
  Node *clone() override;
  void print_tree(ostream &, int) override;
};