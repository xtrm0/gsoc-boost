#include <vector>
#ifndef MAXIMUM
#define MAXIMUM 100000000
#endif
using namespace std;

int main() {
  vector<int> vi;
  for (unsigned int i=0; i<MAXIMUM; i++) {
    vi.push_back(i);
    vi.push_back(-i);
  }
  for (unsigned int i=0; i<vi.size(); i++) {
    vi[i]++;
  }
}
