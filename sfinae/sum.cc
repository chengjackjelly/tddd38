#include <vector>      // std::vector
#include <string>      // std::string
#include <type_traits> // std::enable_if
#include <cstddef>     // size_t
#include <iostream>

using std::cout;
using std::endl;

/*
  1. we want to check that the for-loop will work
    - to check this, we can look for the .begin() function
    - must be possible to dereference iterators
  2. The types inside the container must be addable

  This is done by checking that this is a valid expression:
  *v.begin() + *v.begin()

  NOTE: the expression above is never evaluated, the compiler will
  just check that it is valid.
  
  the first parameter is an int, this is to induce a priority
  on our functions.

  There is a generate sum_helper that can match any type
  This means that if this sum_helper overload matches, there
  are two versions that simultaneously match => ambiguous function
  call.

  BUT we pass '0' as the first parameter. For this overload its an
  exact match, since '0' is an int. The more general template has a
  float as first parameter, so the compiler would have to perform a
  conversion to call it. What this means is that the compiler will not
  choose the general template UNLESS there are no other appropriate
  functions to call (and in that case it will convert '0' to a float
  and call the general solution).
 */
template <typename T>
auto sum_helper(int, T const& v)
  -> decltype(*v.begin() + *v.begin())
{
  typename T::value_type result{};
  /*
    this is called a range-based for-loop
    They are syntactical sugar for an iterator loop:

    for (auto it = v.begin(); it != v.end(); ++it)
    {
      // ...
    }
   */
  for (auto e : v)
  {
    result = result + e;
  }
  return result;
}

/*
  Match an array, just like the previous sum_helper this would be
  in conflict with the general one if we didn't take an 'int' as the
  first parameter.
 */
template <typename T, size_t N>
auto sum_helper(int, T const (&a)[N])
  -> decltype(a[0] + a[1])
{
  auto result{a[0]};
  for (int i{1}; i < N; ++i)
  {
    result = result + a[i];
  }
  return result;
}

/*
  This is a sink, it will match anything that the other sum_helper
  functions won't match. This has lower priority in the overload resolution
  since the compiler would have to convert the '0' to a float, while the
  other overloads do not require any implicit type conversions.
 */
template <typename T>
T sum_helper(float, T const& t)
{
  return t;
}

// Call sum_helper for appropriate types
template <typename T>
auto sum(T const& t)
{
  return sum_helper(0, t);
}

/*
  Variadic version of sum that will sum all the passed parameters
  If the number of arguments is 1 it would be in conflict with the
  sum overload above, so we would like to disallow it. Therefore
  we use enable_if to check if the size of Ts is greater than 1.

  If it is greater than 1, this function is enabled and is in
  no conflict with any other sum overload.

  If the count is less than or equal to 1, enable_if would trigger
  SFINAE and disallow this overload, thus making all sum overloads
  mutually exclusive.

  Second argument of enable_if_t is the return type of this function.
  We check that all the arguments in 'args' can be summed together, if
  they are not this overload would be disallowed.
 */
template <typename... Ts>
auto sum(Ts &&... args)
  -> std::enable_if_t<(sizeof...(Ts) > 1),
                      decltype((... + args))>
{
  // use fold-expressions (C++17) to sum all the passed arguments.
  return (... + args);
}

int main()
{
  std::vector<std::string> words{
    "SFINAE", " ", "is", " ", "life"};
  double arr[3] {1.0506, 1.0405, 1.0504};
  std::string money{"*"};

  // will print "SFINAE is life"
  cout << sum(words) << endl;

  // will print 3.1415
  cout << sum(arr)   << endl;

  // std::string is technically a container
  // so this will just sum the characters in
  // the string and convert them to int (because
  // adding characters promotes them to ints)
  // so this will print 42
  cout << sum(money) << endl;

  // will print 0
  cout << sum(1u, 0.5, -2, 3.5f, -3) << endl;

  // will print 1
  cout << sum(1) << endl;
}