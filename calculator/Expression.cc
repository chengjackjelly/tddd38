#include "Expression.h"

#include <stdexcept>
#include <ostream>

/* Implement Expression here */
Expression::Expression(Expression const &other)
{
    this->root = other.root->clone();
}
Expression::Expression(Expression &&other) : root(other.root)
{
    other.root = nullptr;
}
Expression::~Expression()
{
    this->root->~Node();
}
Expression &Expression::operator=(Expression const &rhs)
{
    Expression copy{rhs};
    std::swap(root, copy.root);
    return *this;
}
Expression &Expression::operator=(Expression &&rhs)
{
    std::swap(root, rhs.root);
    return *this;
}
double Expression::evaluate() const
{
    return this->root->evaluate();
}
void Expression::print_tree(std::ostream &os) const
{
    this->root->print_tree(os, 1);
}
void Expression::print(std::ostream &os) const
{
    this->root->print(os);
}
/* For part B */
// void print(std::ostream& os) const
// {
//     throw std::invalid_argument{"--print is unimplemented"};
// }

/* For part C */
void Expression::expand()
{
    this->root = this->root->expand();
}
