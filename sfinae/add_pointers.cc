#include <type_traits>

namespace details
{
    template <bool N, typename T = void>
    using enable_if_t = typename std::enable_if<N, T>::type;

    // implement add_pointers function template here
    template <typename T, typename U>
    T add_pointers_helper(enable_if_t<!std::is_pointer<U>::value , int> = {}){
        // return add_pointers_helper<T*,std::remove_pointer<U>::type>();
        T a;
        return a;
    }

    template <typename T, typename U , typename=enable_if_t<std::is_pointer<U>::value>,typename V=typename std::remove_pointer<U>::type>
    auto add_pointers_helper(enable_if_t<std::is_pointer<U>::value , int> = {})
{
        return add_pointers_helper<T*,V>();
        
    }
    

    
}

template <typename T, typename U>
struct add_pointers
{
  using type = decltype(details::add_pointers_helper<T, U>());
};

int main()
{
  static_assert(std::is_same_v<add_pointers<int, int>::type, int>, "int + int = int");
  static_assert(std::is_same_v<add_pointers<int, int*>::type, int*>, "int + int* = int*");
  static_assert(std::is_same_v<add_pointers<int*, int*>::type, int**>, "int* + int* = int**");
  static_assert(std::is_same_v<add_pointers<int**, int*>::type, int***>, "int** + int* = int**");
  static_assert(std::is_same_v<add_pointers<int**, int***>::type, int*****>, "int** + int*** = int*****");
}