#include <iostream>

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

  return 0;
}
