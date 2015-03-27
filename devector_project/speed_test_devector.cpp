#include "devector.hpp"
#ifndef MAXIMUM
#define MAXIMUM 100000000
#endif
using namespace boost;

int main() {
  devector<int> vi;
  for (unsigned int i=0; i<MAXIMUM; i++) {
    vi.push_back(i);
    vi.push_front(-i);
  }
  for (unsigned int i=0; i<vi.size(); i++) {
    vi[i]++;
  }
}
