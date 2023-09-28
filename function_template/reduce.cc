#include <cstddef> // gives access to size_t
#include <iostream>
#include <string>

using namespace std;

/*
  Your code here
 */
template <typename T, size_t N>
T reduce(T (&&p)[N],T first=0, T (*ptr)(T const&,T const&)=nullptr){
    T sumup=first;
    for(int i=0;i<N;i++){
        if(ptr)
        sumup=(*ptr)(sumup,*(p+i));
        else
        sumup+=*(p+i);
    }
    return sumup;
 }
template <typename T, size_t N>
T reduce(T (&p)[N],T first=0, T (*ptr)(T const&,T const&)=nullptr){
    T sumup=first;
    for(int i=0;i<N;i++){
        if(ptr)
        sumup=(*ptr)(sumup,*(p+i));
        else
        sumup+=*(p+i);
    }
    return sumup;
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
    int a[]={1,2,3,4,5};
    cout << reduce({1,2,3,4,5}) << endl;
cout << reduce(pi, 3.0) << endl;
    cout << reduce(factorial, 1.0, multiply) << endl;
    cout << reduce(concat, "hello"s) << endl;

}