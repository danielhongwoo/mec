#include <iostream>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

#define print_type(var) do { \
  std::cout << type_id_with_cvr<decltype(var)>().pretty_name() << std::endl; \
} while(0)


int main() {
  auto x = 1;
  const auto cx = x;
  const auto& rx = x;

  print_type(x);
  print_type(cx);
  print_type(rx);

  auto&& ur1 = x;
  auto&& ur2 = cx;
  auto&& ur3 = 1;
  print_type(ur1);
  print_type(ur2);
  print_type(ur3);

  auto il1 = { 1 };
  print_type(il1);

  // deduced to just int. the book is outdated. 
  // http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2014/n3922.html
  auto il2{ 1 };
  print_type(il2);

  return 0;
}
