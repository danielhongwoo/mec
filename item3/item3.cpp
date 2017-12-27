#include <iostream>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

#define print_type(var) do { \
  std::cout << type_id_with_cvr<decltype(var)>().pretty_name() << std::endl; \
} while(0)

int main() {
  int i = 0;
  decltype(i) a = 2;

  print_type(i);
  print_type(a);

  return 0;
}
