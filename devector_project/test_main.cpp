#include "devector.hpp"
#include <iostream>
#include <string>
using namespace boost;
using namespace std;

void test_int(int till) {
  devector<int> vi;
  int *x;

  /*
    Contructors test
   */
  
  for (int i=0; i<till; i++) {
    x = new int(i);
    try {
      vi.push_back(*x);
    } catch(int e) {
      std::cout << std::endl << "exception : ";
    }
    delete x;
    cout << vi[i] << " " << vi.size() << " " << vi.capacity() << endl;
  }

  /*
    Iterator test
   */
  for (devector<int>::iterator x = vi.begin(); x!=vi.end(); x+=1) {
    cout << *x << endl;
  }
}

void test_push_front(int till) {
  devector<int> vi;

  /*
    Contructors test
   */
  
  for (int i=0; i<till; i++) {
    vi.push_back(i);
    vi.push_front(-i);
    cout << vi.front() << ":" << vi.back() << " " << vi.size() << " " << vi.capacity() << endl;
  }
  for (int i=0; i<vi.size(); i++) {
    cout << vi[i] << endl;
  }
}

void test_string() {
  devector<string> vs;
  vs.push_back(string("ola mundo"));
  cout << vs[0] << endl;
  vs.push_back(string("ola mundo1"));
  cout << vs[1] << endl;
  vs.push_back(string("ola mundo2"));
  cout << vs[2] << endl;
}


int main() {
  /*
    test_int(10);
    test_string();
    devector<devector<devector<int> > > vc;
    cout <<  sizeof(devector<int>) << " " << vc.max_size() << endl;
  */
  test_push_front(10);
  return 0;
}
