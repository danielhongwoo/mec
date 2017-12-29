#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

#define print_type(var) do { \
  std::cout << type_id_with_cvr<decltype(var)>().pretty_name() << std::endl; \
} while(0)

template <typename T>
class Widget {
public:
  Widget(int n) {
    for (auto i = 0; i < 10; ++i)
      a_[i] = i * n;
  }
  const auto& a() const { return a_; }
private:
  std::array<T, 10> a_;
};

template <typename T>
std::vector<bool> f(const Widget<T>& w) {
  const auto a = w.a();
  std::vector<bool> v;
  std::for_each(a.begin(),
                a.end(),
                [&v](const T& i) {
                  v.push_back((i % 2 == 0));
                });
  return v;
}

int main() {
  Widget<int> w(3);
  auto v1 = f<int>(w)[5];
  print_type(v1); // it's not bool type. on clang 4.0: std::_Bit_reference

  // invisible proxy types can cause auto to deduce the wrong type for an
  // initializing expression.
  // ex) std::vector<bool>::operator[]

  // explicitly typed initializer idiom
  auto v2 = static_cast<bool>(f<int>(w)[5]);
  print_type(v2); // now it's bool

  // But I think it's better solution to use just bool v = f<int>w[5];
  bool v3 = f<int>(w)[5];
  print_type(v3);

  return 0;
}
