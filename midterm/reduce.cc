#include <cstddef> // gives access to size_t
#include <iostream>
#include <string>

using namespace std;

/*
  Your code here
 */

 template<typename T>
 T add(T const&lhs, T const&rhs){
    return lhs+rhs;
 }
 template<typename T,size_t N>
 T reduce( const T (&arr)[N],T x={}, T (*ptr)(T const&, T const&)= add){
    for(int i=0;i<N;i++){
        x=(*ptr)(x,arr[i]);
    }
    return x;
 }

double multiply(double const& lhs, double const& rhs)
{
    return lhs * rhs;
}

int main()
{
    double pi[]{0.0505, 0.0505, 0.0405};
    double factorial[]{1.0, 2.0, 3.0, 4.0, 5.0};
    string concat[]{" ", "world"};
    cout << reduce({1,2,3,4,5}) << endl;
    cout << reduce(pi, 3.0) << endl;
    cout << reduce(factorial, 1.0, multiply) << endl;
    cout << reduce(concat, "hello"s) << endl;
}