#include <iostream>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

#define print_type(T) do { \
  std::cout << __FUNCTION__ << " "\
      << "T = " << type_id_with_cvr<T>().pretty_name() \
      << " ,param = " << type_id_with_cvr<decltype(param)>().pretty_name() << std::endl; \
} while(0)

template<typename T>
void by_ref(T& param) {
  print_type(T);
}

template<typename T>
void by_const_ref(const T& param) {
  print_type(T);
}

template<typename T>
void by_pointer(T* param) {
  print_type(T);
}

template<typename T>
void by_universal_ref(T&& param) {
  print_type(T);
}

template<typename T>
void by_value(T param) {
  print_type(T);
}

void myfunc(int* param) {
}

int main() {

  int x = 1;
  const int cx = x;
  const int& rx = x;

  // case 1
  by_ref(x);
  by_ref(cx);
  by_ref(rx);

  by_const_ref(x);
  by_const_ref(cx);
  by_const_ref(rx);

  by_pointer(&x);
  by_pointer(&cx);
  by_pointer(&rx);


  // case 2
  // if expr is an lvalue, both T and Param are deduced to be lvalue refereneces.
  by_universal_ref(x);
  by_universal_ref(cx);
  by_universal_ref(rx);
  by_universal_ref(1);

  // case 3
  by_value(x);
  by_value(cx);
  by_value(rx);
  by_value(1);


  // array arguments
  const char name[] = "abc";
  by_value(name);
  by_ref(name);

  // function argements
  by_value(myfunc);
  by_ref(myfunc);

  return 0;
}




























/*
by_ref T = int ,param = int&
by_ref T = int const ,param = int const&
by_ref T = int const ,param = int const&
by_const_ref T = int ,param = int const&
by_const_ref T = int ,param = int const&
by_const_ref T = int ,param = int const&
by_pointer T = int ,param = int*
by_pointer T = int const ,param = int const*
by_pointer T = int const ,param = int const*
by_universal_ref T = int& ,param = int&
by_universal_ref T = int const& ,param = int const&
by_universal_ref T = int const& ,param = int const&
by_universal_ref T = int ,param = int&&
by_value T = int ,param = int
by_value T = int ,param = int
by_value T = int ,param = int
by_value T = int ,param = int
by_value T = char const* ,param = char const*
by_ref T = char const [4] ,param = char const (&) [4]
by_value T = void (*)(int*) ,param = void (*)(int*)
by_ref T = void (int*) ,param = void (&)(int*)
*/
