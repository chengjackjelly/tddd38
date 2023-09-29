#include "Node.h"
#include <iomanip>
#include <iostream>
/*
  Implement the functionality of the Node hierarchy
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
Number::Number(double v)
{
  this->value = v;
}
Operator::Operator(Node *left, Node *right)
{
  this->left = left;
  this->right = right;
}
double Number::evaluate()
{
  return this->value;
}
double Addition::evaluate()
{
  return (this->left)->evaluate() + (this->right)->evaluate();
}
double Subtraction::evaluate()
{
  return (this->left)->evaluate() - (this->right)->evaluate();
}
double Multiplication::evaluate()
{
  return (this->left)->evaluate() * (this->right)->evaluate();
}
double Division::evaluate()
{
  return (this->left)->evaluate() / (this->right)->evaluate();
}
void Number::print_tree(ostream &out, int indentation)
{
  out << std::setw(indentation) << this->value << std::endl;
}
void Number::print(std::ostream &os)
{
  os << this->value;
}
void Addition::print(ostream &os)
{
  this->left->print(os);
  if (typeid(Addition) == typeid(*this))
  {
    os << "+";
  }
  else
  {
    os << "-";
  }
  this->right->print(os);
}
void Addition::print_tree(ostream &out, int indentation)
{
  (this->left)->print_tree(out, indentation + 2);
  out << std::setw(indentation + 1) << "/" << std::endl;
  out << std::setw(indentation) << "+" << std::endl;
  out << std::setw(indentation + 1) << "\\" << std::endl;
  (this->right)->print_tree(out, indentation + 2);
}
void Subtraction::print_tree(ostream &out, int indentation)
{
  (this->left)->print_tree(out, indentation + 2);
  out << std::setw(indentation + 1) << "/" << std::endl;
  out << std::setw(indentation) << "-" << std::endl;
  out << std::setw(indentation + 1) << "\\" << std::endl;
  (this->right)->print_tree(out, indentation + 2);
}
void Multiplication::print(ostream &os)
{
  if (dynamic_cast<Addition *>(this->left))
  {
    os << "(";
    this->left->print(os);
    os << ")";
  }
  else
  {
    this->left->print(os);
  }
  if (typeid(Multiplication) == typeid(*this))
  {
    os << "*";
  }
  else
  {
    os << "/";
  }

  if (dynamic_cast<Addition *>(this->right))
  {
    os << "(";
    this->right->print(os);
    os << ")";
  }
  else
  {
    this->right->print(os);
  }
}
void Multiplication::print_tree(ostream &out, int indentation)
{
  (this->left)->print_tree(out, indentation + 2);
  out << std::setw(indentation + 1) << "/" << std::endl;
  out << std::setw(indentation) << "*" << std::endl;
  out << std::setw(indentation + 1) << "\\" << std::endl;
  (this->right)->print_tree(out, indentation + 2);
}
void Division::print_tree(ostream &out, int indentation)
{
  (this->left)->print_tree(out, indentation + 2);
  out << std::setw(indentation + 1) << "/" << std::endl;
  out << std::setw(indentation) << "/" << std::endl;
  out << std::setw(indentation + 1) << "\\" << std::endl;
  (this->right)->print_tree(out, indentation + 2);
}
Node *Number::clone()
{
  // std::cout << this->value << std::endl;
  return new Number(this->value);
}
Node *Addition::clone()
{
  Node *cpLeft = (this->left)->clone();
  Node *cpRight = (this->right)->clone();
  Node *cpRoot = new Addition(cpLeft, cpRight);
  return cpRoot;
}
Node *Subtraction::clone()
{
  Node *cpLeft = (this->left)->clone();
  Node *cpRight = (this->right)->clone();
  Node *cpRoot = new Subtraction(cpLeft, cpRight);
  return cpRoot;
}
Node *Multiplication::clone()
{
  Node *cpLeft = (this->left)->clone();
  Node *cpRight = (this->right)->clone();
  Node *cpRoot = new Multiplication(cpLeft, cpRight);
  return cpRoot;
}
Node *Division::clone()
{
  Node *cpLeft = (this->left)->clone();
  Node *cpRight = (this->right)->clone();
  Node *cpRoot = new Division(cpLeft, cpRight);
  return cpRoot;
}
Operator::~Operator()
{
  delete this->left;
  delete this->right;
  std::cout << "Operator destructor" << std::endl;
}
Node *Number::expand()
{
  return this;
}
Node *Operator::expand()
{
  this->left = this->left->expand();
  this->right = this->right->expand();
  // this->left->print_tree(std::cout, 1);
  // this->right->print_tree(std::cout, 1);
  if (typeid(*this) == typeid(Multiplication))
  {
    if (dynamic_cast<Addition *>(this->left))
    {
      auto current = Operator::left_expand(this);

      return current->expand();
    }
    else if (dynamic_cast<Addition *>(this->right))
    {
      auto current = Operator::right_expand(this);
      return current->expand();
    }
  }
  return this;
}
Node *Operator::left_expand(Operator *root)
{
  Operator *ltree = dynamic_cast<Operator *>(root->left);
  Node *a = ltree->left;
  Node *b = ltree->right;
  Node *c = root->right;
  root->left = a;
  ltree->left = root;
  if (typeid(*root) == typeid(Multiplication))
  {

    ltree->right = new Multiplication(b, c->clone());
  }
  else
  {
    ltree->right = new Division(b, c->clone());
  }
  return ltree;
}
Node *Operator::right_expand(Operator *root)
{
  Operator *rtree = dynamic_cast<Operator *>(root->right);
  Node *a = root->left;
  Node *b = rtree->left;
  Node *c = rtree->right;
  root->right = b;
  rtree->left = root;
  if (typeid(*root) == typeid(Multiplication))
  {
    rtree->right = new Multiplication(a->clone(), c);
  }
  else
  {
    rtree->right = new Division(a->clone(), c);
  }
  return rtree;
}