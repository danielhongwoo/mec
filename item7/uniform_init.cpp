#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "print_type.h"

using namespace std;

class Item {
public:
  Item(int i, bool b) : i_(i), b_(b), d_(0.0) { cout << "first" << endl; }
  Item(int i, double d) : i_(i), b_(false), d_(d) { cout << "second" << endl;}
  Item(std::initializer_list<long double> il) {
    cout << "third: ";
    for (auto i : il) cout << i << " ";
    cout << endl;
  }
  void print() { cout << i_ << " " << b_ << " " << d_ << endl; }
  operator float() const {
    cout << __FUNCTION__ << endl;
    return d_;
  }
  operator double() const {
    cout << __FUNCTION__ << endl;
    return d_;
  }
private:
  int i_;
  bool b_;
  double d_;
};

class ItemBool {
public:
  ItemBool(int i, bool b) : i_(i), b_(b), d_(0.0) { cout << "first" << endl; }
  ItemBool(int i, double d) : i_(i), b_(false), d_(d) { cout << "second" << endl;}
  ItemBool(std::initializer_list<bool> il) {
    cout << "third: ";
    for (auto i : il) cout << i << " ";
    cout << endl;
  }
  void print() { cout << i_ << " " << b_ << " " << d_ << endl; }
  operator float() const {
    cout << __FUNCTION__ << endl;
    return d_;
  }
  operator double() const {
    cout << __FUNCTION__ << endl;
    return d_;
  }
private:
  int i_;
  bool b_;
  double d_;
};

class ItemString {
public:
  ItemString(int i, bool b) : i_(i), b_(b), d_(0.0) { cout << "first" << endl; }
  ItemString(int i, double d) : i_(i), b_(false), d_(d) { cout << "second" << endl;}
  ItemString(std::initializer_list<std::string> il) {
    cout << "third: ";
    for (auto i : il) cout << i << " ";
    cout << endl;
  }
  void print() { cout << i_ << " " << b_ << " " << d_ << endl; }
  operator float() const {
    cout << __FUNCTION__ << endl;
    return d_;
  }
  operator double() const {
    cout << __FUNCTION__ << endl;
    return d_;
  }
private:
  int i_;
  bool b_;
  double d_;
};

class ItemEmpty {
public:
  ItemEmpty() { cout << "first" << endl; }
  ItemEmpty(std::initializer_list<std::string> il) {
    cout << "second: ";
    for (auto i : il) cout << i << " ";
    cout << endl;
  }
  void print() { cout << __FUNCTION__ << endl; }
private:
};


int main() {
  Item i1(10, true);
  Item i2{10, true}; // call std::initializer_list constructor
  Item i3(10, 1.1);
  Item i4{10, 1.1}; // call std::initializer_list constructor

  Item i5(i3);
  i5.print();
  Item i6{i3}; // oops. probably default copy constructor was called
  i6.print();

  float f = i4;
  double d = i4;
  cout << f << " " << d << endl;

  // ItemBool e1{10, 5.0}; // error. requires narrowing conversions
  
  cout << endl << "ItemString" << endl;
  ItemString is1(10, true);
  ItemString is2{10, true}; // it calls first constructor because
                            // there is no way to convert int and bool to std::string.
  ItemString is3(10, 5.0);
  ItemString is4{10, 5.0};

  ItemEmpty ie1;
  ItemEmpty ie2{};
  ItemEmpty ie3(); // warning: empty parentheses interpreted as a function declaration [-Wvexing-parse]
//  ie3.print();
  ItemEmpty ie4({});

  std::vector<int> v1(10, 2);
  std::vector<int> v2{10, 2};
  for_each(v1.begin(), v1.end(), [](int i) { cout << i << " "; }); cout << endl;
  for_each(v2.begin(), v2.end(), [](int i) { cout << i << " "; }); cout << endl;

  // Design your constructors so that the overload called isn't affected by whether clients use parentheses or braces.
  // in this point of view, std::vector design is bad.

  return 0;
}
