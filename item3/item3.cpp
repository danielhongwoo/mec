#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

#define print_type(var) do { \
  std::cout << type_id_with_cvr<decltype(var)>().pretty_name() << std::endl; \
} while(0)

// c++11
template <typename T>
auto f1(T&& c, int i) -> decltype(forward<T>(c)[i]) {
  return c[i];
}

// TODO what's different?
#if 1
template <typename T>
auto f1_1(T&& c, int i) -> decltype(c[i]) {
  return c[i];
}
#endif

// c++14
template <typename T>
decltype(auto) f2(T&& c, int i) {
  return forward<T>(c)[i];
}

int main() {
  int i = 0;
  decltype(i) a = 2;

  // declared type
  print_type(i);
  print_type(a);
  print_type((a)); // be careful to use ()

  std::vector<int> v = { 1, 2, 3 };
  std::deque<int> d = { 1, 2, 3 };

  f1(v, 1) = 0;
  f2(v, 1) = 1;

  // check parameter bind rvalue 
  auto t = f1(std::vector<int>({1,2,3}), 1);

  return 0;
}
