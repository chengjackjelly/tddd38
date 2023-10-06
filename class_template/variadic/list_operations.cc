#include<iostream>
using namespace std;
template<typename... Ts>
class Pack{
};


template<typename T>
bool contains_helper(T c){
    return false;
}

template<typename T, typename T1, typename... Ts>
bool contains_helper(T c,T1 first, Ts... rest){
    if(typeid(c)== typeid(first)){
        return true;
    }
    return contains_helper(c,rest...);
}

template<typename T, typename... Ts>
bool contains(Pack<Ts...> p){
    T tmp;
    return contains_helper(tmp,Ts{}...);
}

int main(){
    Pack<int,float,char> p;
    bool ret=contains<int>(p);
    if(ret){
        cout<<"correct"<<endl;
    }
}