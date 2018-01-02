#include <iostream>

using namespace std;

class Widget {
public:
  // reference qualifiers
  void foo() & { cout << __FUNCTION__ << " &" << endl; } // when *this is an lvalue
  void foo() && { cout << __FUNCTION__ << " &&" << endl; } // when *this is an rvalue
};

Widget make_widget() {
  return Widget();
}

class B1 {
public:
  virtual void f1() const {}
  virtual void f2(int x) {}
  virtual void f3() & {}
  void f4() const {}
};

class D1 : public B1 {
  // below 4 member functions are not overrided.
  // and g++ 5.4 compiler doesn't generate any warning.
  // and clang 4.0 make some warnings
	//   note: hidden overloaded virtual function 'B1::f1' declared here: different qualifiers (const vs none)
	//   note: hidden overloaded virtual function 'B1::f2' declared here: type mismatch at 1st parameter ('int' vs 'unsigned int')
	//   note: hidden overloaded virtual function 'B1::f3' declared here
  virtual void f1() {}
  virtual void f2(unsigned int x) {}
  virtual void f3() && {}
  virtual void f4() const {}
};

class B2 {
public:
  virtual void f1() const {}
  virtual void f2(int x) {}
  virtual void f3() & {}
  virtual void f4() const {}
};

class D2 : public B2 {
public:
  virtual void f1() const override {}
  virtual void f2(int x) override	{}
  virtual void f3() & override {}
  virtual void f4() const override {}
};

int main() {
  // check reference qualifiers
  Widget w;
  w.foo();
  make_widget().foo();

  return 0;
}
