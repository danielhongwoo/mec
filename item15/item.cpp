#include <iostream>
#include <array>
#include <chrono>

#include "print_type.h"

void func1() {
  // constexpr
  {
    int sz = 10;
    // constexpr auto array_size = sz; // sz's value not known at compilation
                                       // error: constexpr variable 'array_size' must be initialized by a constant expression
    // std::array<int, sz> data; // error: non-type template argument is not a constant expression
    //
    constexpr auto array_size = 10;
    std::array<int, array_size> data;
  }

  // all constexpr objects are const, but not all consts are constexpr.
  {
    int sz;
    const auto array_size = sz;
    print_type(array_size);
    // std::array<int, array_size> data; // array_size's value not known at compilation
  }
}

constexpr int pow(int base, unsigned int exp) noexcept {
  auto result = 1;
  for (unsigned int i = 0; i < exp; ++i) {
    result *= base;
  }
  return result;
}

constexpr long long factorial(long long v) noexcept {
  return v <= 1 ? 1 : (v * factorial(v - 1));
}

long long factorial2(long long v) noexcept {
  return v <= 1 ? 1 : (v * factorial2(v - 1));
}

void func2() {
  std::array<int, pow(3, 5)> results;

  {
    auto start = std::chrono::high_resolution_clock::now();
    constexpr long long a = factorial(20);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "factorial: " << a << " time: " << (end - start).count() << std::endl;

    /*
    constexpr long long a = factorial(21);
    error: constexpr variable 'a' must be initialized by a constant expression
           constexpr long long a = factorial(21);
    note: value 51090942171709440000 is outside the range of representable values of type 'long long'
    */
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long a = factorial2(20);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "factorial: " << a << " time: " << (end - start).count() << std::endl;
  }
}

class Item {
public:
  constexpr Item(int a, int b) : a_(a), b_(b) {}
  constexpr int a() const { return a_; }
  constexpr int b() const { return b_; }
  // setters can be constexpr on c++14
  constexpr void set_a(int a) { a_ = a; }
  constexpr void set_b(int b) { b_ = b; }
private:
  int a_;
  int b_;
};

constexpr Item add(const Item& a, const Item& b) {
  Item t(0, 0);
  t.set_a(a.a() + b.a());
  t.set_b(a.b() + b.b());
  return t;
}

void func3() {
  constexpr Item item(2, 5);
  print_type(item);

  // how to check if constexpr is evaluated correctly at compile time
  // https://stackoverflow.com/questions/28988426/how-to-test-if-constexpr-is-evaluated-correctly
  static_assert(item.a() == 2, "a should be 2");

  constexpr Item item2(3, 6);
  constexpr Item item3 = add(item, item2);

  static_assert(item3.a() == 5, "a should be 2");
}

int main() {
  func1();
  func2();
  func3();

  return 0;
}
