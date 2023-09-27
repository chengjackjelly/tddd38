#include <iostream>
#include "Parser.cc"
#include <cctype>
#include <istream>
#include <sstream>
using namespace std;
int main()
{
    // Node a;
    // Node f;
    // Number b{1.0};
    // Operator o{new Node(), new Node()};
    // Addition m{new Node(), new Node()};

    string const &expression = "(1+7)*(2-9)";
    istringstream iss{expression};
    Node *res = parse_expression(iss);
    Node *cpres = res->clone();
    cout << typeid(Addition).hash_code() << endl;
    res->print_tree(cout, 1);
    cpres->print_tree(cout, 1);
    // cout << typeid(a).hash_code() << " " << typeid(b).hash_code() << " " << typeid(o).hash_code() << " " << typeid(*res).hash_code() << endl;
    // char c;
    // /* "..."s denotes a std::string literal rather than a char const*
    //  * literal. Quite handy since we can use + on them. */
    // if (iss >> c)
    //     throw parser_error{"Unexpected token '"s + c + "' found"};
    delete cpres;
    delete res;
}
