#include <iostream>
#include <vector>
#include <deque>
#include <functional>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <string>
#include <unordered_map>
using namespace std;

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

#define print_type(var) do { \
  std::cout << type_id_with_cvr<decltype(var)>().pretty_name() << std::endl; \
} while(0)

template <typename T>
void iterate_no_auto(T b, T e) {
  while (b != e) {
    typename std::iterator_traits<T>::value_type v = *b;
    cout << v << " ";
    ++b;
  }
  cout << endl;
}

template <typename T>
void iterate_auto(T b, T e) {
  while (b != e) {
    auto v = *b;
    cout << v << " ";
    ++b;
  }
  cout << endl;
}

class Widget {
public:
  Widget(int i) : i_(i) {}
  bool operator<(const Widget& o) { return o.value() > i_; }
  int value() const { return i_; };
private:
  int i_;
  int dummy_[1024];
};

int main() {
  vector<int> v = { 1, 2, 3};

  // less typing
  iterate_no_auto(v.begin(), v.end());
  iterate_auto(v.begin(), v.end());


  //
  // performance difference between auto and std::function
  { 
    auto less1 = [](const auto& p1, const auto& p2) {
      return *p1 < *p2;
    };
    std::cout << "size of less1: " << sizeof(less1) << endl;

    function<bool(const std::unique_ptr<Widget>&,
                  const std::unique_ptr<Widget>&)>
        less2 = [](const std::unique_ptr<Widget>& p1,
                   const std::unique_ptr<Widget>& p2) {
          return *p1 < *p2;
        };
    std::cout << "size of less2: " << sizeof(less2) << endl;

    {
      // auto
      std::vector<std::unique_ptr<Widget>> ws1;
      for (auto i = 0; i < 1024*100; ++i) {
        ws1.emplace_back(new Widget(std::rand()));
      }

      auto start = std::chrono::high_resolution_clock::now();
      std::sort(ws1.begin(), ws1.end(), less1);
      auto end = std::chrono::high_resolution_clock::now();
      cout << ws1[0].get()->value() << " time: " << (end - start).count() << endl;
    }

    {
      // std::function
      // 25% slower than using auto
      std::vector<std::unique_ptr<Widget>> ws2;
      for (auto i = 0; i < 1024*100; ++i) {
        ws2.emplace_back(new Widget(std::rand()));
      }

      auto start = std::chrono::high_resolution_clock::now();
      std::sort(ws2.begin(), ws2.end(), less2);
      auto end = std::chrono::high_resolution_clock::now();
      cout << ws2[0].get()->value() << " time: " << (end - start).count() << endl;
    }
  }

  {
    std::unordered_map<std::string, int> m;
    for (auto i = 0; i < 1024*1024; ++i) {
      m.insert(std::make_pair("abcd", std::rand()));
    }

    {
      auto sum = 0;
      auto start = std::chrono::high_resolution_clock::now();
      for (const std::pair<std::string, int>& p : m) {
        // way slower
        // oops it's different type
        sum += p.second;
      }
      auto end = std::chrono::high_resolution_clock::now();
      cout << "sum: " << sum << " time: " << (end - start).count() << endl;
    }

    {
      auto sum = 0;
      auto start = std::chrono::high_resolution_clock::now();
      for (const std::pair<const std::string, int>& p : m) {
        // much faster but slower than using auto.
        // similar type but still something is different.
        // or it takes additional time to make a new variable and release it every loop.
        sum += p.second;
      }
      auto end = std::chrono::high_resolution_clock::now();
      cout << "sum: " << sum << " time: " << (end - start).count() << endl;
    }

    {
      auto sum = 0;
      for (const auto& p : m) 
        print_type(p);

      auto start = std::chrono::high_resolution_clock::now();
      for (const auto& p : m)
        sum += p.second;

      // 40 times faster than using manual type. g++ 5.4
      auto end = std::chrono::high_resolution_clock::now();
      cout << "sum: " << sum << " time: " << (end - start).count() << endl;
    }

    /*
     * sum: 206707168 time: 4672
     * sum: 206707168 time: 100
     * std::pair<std::__cxx11::basic_string<char, std::char_traits<char>,
     * std::allocator<char> > const, int> const&
     * sum: 206707168 time: 84
     */
  }

  return 0;
}
