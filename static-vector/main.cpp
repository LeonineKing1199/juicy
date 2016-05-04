#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstring>

#include "./include/static-vector.hpp"

int main(void)
{
  // it should be default constructible
  regulus::static_vector<int, 32> vec;
  assert(vec.size() == 0);
  
  // we should be able to emplace_back elements...
  for (int i = 0; i < 32; ++i) {
    vec.emplace_back(i);
  }

  for (int i = 0; i < 32; ++i) {
    assert(vec[i] == i);
  }
  
  assert(vec.size() == 32);
  
  // it should be STL-compliant and offer element access...
  std::for_each(
    vec.begin(), vec.end(),
    [](int& val)
    {
      val *= 2;
    });
  
  for (int i = 0; i < 32; ++i) {
    assert(vec[i] == (i * 2));
  }
  
  // it should support try-catchable element access...
  try {
    int cpy = vec.at(vec.size() * 4); // oh no!!!
    assert(cpy == 1337);
  } catch(std::exception& e) {
    assert(std::strcmp(e.what(), "Index is out of bounds!") == 0);
  }
  
  // it should support front/back access
  assert(vec.front() == 0);
  assert(vec.back() == (31 * 2));
  
  // it should support some const stuff
  regulus::static_vector<int, 32> const& ref = vec;
  for (int i = 0; i < (int ) ref.size(); ++i) {
    assert(ref[i] == (i * 2));
  }
  
  return 0;  
}
