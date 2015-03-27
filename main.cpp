#include "vector.hpp"
#include <iostream>
#include <string>
int main() {
  boost::vector<int> vi;
  for (boost::vector<int>::size_type i=0; i<100; i++) {
    vi.pre_push_back();
    vi.push_back(i);
  }
  for (boost::vector<int>::size_type i=0; i<vi.size(); i++) {
    std::cout << vi[i] << std::endl;
  }
  vi.clear();
  for (boost::vector<int>::size_type i=0; i<100; i++) {
    vi.pre_push_back();
    vi.push_back(i);
  }
  for (boost::vector<int>::size_type i=0; i<vi.size(); i++) {
    std::cout << vi[i] << std::endl;
  }
  vi.clear();
  typedef int type3;
  boost::vector<type3> vi3({1,2,4,5,2,3});
  for (boost::vector<type3>::size_type i=0; i<vi3.size(); i++) {
    std::cout << vi3[i] << std::endl;
  }
  typedef std::string type;
  boost::vector<type> vi2({type("abc"),type("def"),type("wahttheguck"),type("duck"),type("duck"),type("goose")});
  std::cout << "a" << std::endl;
  for (boost::vector<type>::size_type i=0; i<vi2.size(); i++) {
    std::cout << vi2[i] << std::endl;
  }
}
