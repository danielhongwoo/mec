// it's from https://shaharmike.com/cpp/lambdas-and-functions/

#include <iostream>
#include <functional>
#include <array>
#include <cstdlib>

using namespace std;

void* operator new(std::size_t n) {
  cout << "Allocating " << n << " bytes" << endl;
  return malloc(n);
}
void operator delete(void* p) throw() {
  free(p);
}

int main() {
  std::array<char, 16> arr1;
  auto lambda1 = [arr1](){}; 
  cout << "Assigning lambda1 of size " << sizeof(lambda1) << endl;
  std::function<void()> f1 = lambda1;
  cout << "Assigning f1 of size " << sizeof(f1) << endl;

  // 17. That’s the threshold beyond which std::function reverts to dynamic
  // allocation (on clang). Note that the allocation is for the size of 17 bytes
  // as the lambda object needs to be contiguous in memory.
  std::array<char, 17> arr2;
  auto lambda2 = [arr2](){}; 
  cout << "Assigning lambda2 of size " << sizeof(lambda2) << endl;
  std::function<void()> f2 = lambda2;
  cout << "Assigning f2 of size " << sizeof(f2) << endl;
  return 0;
}
