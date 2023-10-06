// Implement is_const, is_pointer, is_array and is_const_pointer here
struct share_true{
  static bool const value { true };
};
struct share_false{
  static bool const value { false };
};

template<typename T>
struct is_const: share_false{
};


template<typename T>
struct is_const <T const> : share_true{
};


template<typename T>
struct is_pointer: share_false{
  
};


template<typename T>
struct is_pointer <T*> : share_true {

};

template<typename T>
struct is_pointer <T* const> : share_true {

};
template<typename T>
struct is_array: share_false{
  
};


template<typename T,int N>
struct is_array <T[N]> : share_true {

};

template<typename T>
struct is_const_pointer: share_false{
  
};


template<typename T>
struct is_const_pointer <T* const> : share_true {
};


int main()
{ 
  static_assert(is_const<int const>::value, "is_const failed for 'int const'");
  static_assert(is_const<int* const>::value, "is_const failed for 'int* const'");
  static_assert(!is_const<int>::value, "is_const failed for 'int'");
  static_assert(!is_const<int const*>::value, "is_const failed for 'int const*'");

  static_assert(is_pointer<int*>::value, "is_pointer failed for 'int*'");
  static_assert(is_pointer<int const*>::value, "is_pointer failed for 'int const*'");
  static_assert(is_pointer<int* const>::value, "is_pointer failed for 'int* const'");
  static_assert(!is_pointer<int>::value, "is_pointer failed for 'int'");

  static_assert(is_array<int[5]>::value, "is_array failed for 'int[5]'");
  static_assert(is_array<int const[7]>::value, "is_array failed for 'int const[7]'");
  static_assert(!is_array<int>::value, "is_array failed for 'int'");

  static_assert(is_const_pointer<int* const>::value, "is_const_pointer failed for 'int* const'");
  static_assert(!is_const_pointer<int*>::value, "is_const_pointer failed for 'int*'");
  static_assert(!is_const_pointer<int>::value, "is_const_pointer failed for 'int'");
  static_assert(!is_const_pointer<int const>::value, "is_const_pointer failed for 'int const'");
}