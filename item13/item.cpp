#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "print_type.h"

int main() {
  std::vector<int> values = { 1, 2, 3, 4, 5 };
  auto it = std::find(values.cbegin(), values.cend(), 5);
  std::vector<int>::const_iterator cit = std::find(values.cbegin(), values.cend(), 5);
  print_type(it);
  print_type(cit);
  values.insert(it, 7);
  for_each(values.cbegin(), values.cend(), [] (int i) { std::cout << i << std::endl; });
  auto ncit = std::find(values.begin(), values.end(), 5);
  print_type(ncit);
  *ncit = 10;
  for_each(values.cbegin(), values.cend(), [] (int i) { std::cout << i << std::endl; });

  auto it2 = std::find(std::cbegin(values), std::cend(values), 5);
  std::vector<int>::const_iterator cit2 = std::find(std::cbegin(values), std::cend(values), 5);
  print_type(it2);
  print_type(cit2);
  values.insert(it2, 8);
  for_each(values.cbegin(), values.cend(), [] (int i) { std::cout << i << std::endl; });

  return 0;
}
