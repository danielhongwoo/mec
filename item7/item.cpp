#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <atomic>

#include "print_type.h"
using namespace std;

class Widget {
public:
  Widget() {}
  void prit() {
    std::cout << x + y + z << std::endl;
  }
private:
  int x { 0 };
  int y = 0;
  // int z(0); // compile error
  int z = { 0 };
};

int main() {
  {
    int x(0);
    int y = 0;
    int z{ 0 };
    int z1 = { 0 };
    print_type(x);
    print_type(y);
    print_type(z);
    print_type(z1);
  }

  {
    auto x(0);
    auto y = 0;
    auto z{ 0 };
    auto z1 = { 0 };
    print_type(x);
    print_type(y);
    print_type(z);
    print_type(z1);
  }

  // uniform initialization (braced initialization)
  std::vector<int> v = { 1, 2, 3, 4, 5};

  Widget w;

  std::atomic<int> ai1 {0};
  std::atomic<int> ai2 (0);
//  std::atomic<int> ai3 = 0;
  std::atomic<int> ai4 = {0};

#if 0
  double x, y;
  int s = { x + y };
  // error: type 'double' cannot be narrowed to 'int' in initializer list
#endif

  double x = 0.1, y = 1.2;
  int s = x + y; // narrowed without any errors and warnings
  cout << s << endl;

  return 0;
}
