#include "vector.hpp"
#include <string>
#define BOOST_TEST_DYN_LYNK
#define BOOST_TEST_MODULE BoostExampleVector
#include <boost/test/included/unit_test.hpp>
/*
  This file includes unit tests for vector<int> and for vector<string>
 */

/*
  ==========================
  Vector<int> tests
  ==========================
*/

//Tests basic vector<int> allocation
BOOST_AUTO_TEST_CASE(vector_int_base_test_0) {
  BOOST_CHECK_NO_THROW(boost::vector<int> vi1);
  BOOST_CHECK_NO_THROW(boost::vector<int> vi2(10));
  BOOST_CHECK_NO_THROW(boost::vector<int> vi3({1,2,3}));
}

//Tests basic vector<int> constructor vector<int>() and vector<int>(size_type)
BOOST_AUTO_TEST_CASE(vector_int_base_test_1) {
  boost::vector<int> vi;
  
  BOOST_CHECK(vi.size()==0);
  BOOST_CHECK(vi.capacity()==0);
  BOOST_CHECK(vi.begin()==vi.end());
  BOOST_CHECK_THROW(vi[0], boost::exceptions::out_of_bounds);

  boost::vector<int> vi2(10);
  
  BOOST_CHECK(vi2.size()==0);
  BOOST_CHECK(vi2.capacity()==10);
  BOOST_CHECK(vi2.begin()==vi2.end());
  BOOST_CHECK_THROW(vi2[0], boost::exceptions::out_of_bounds);

  boost::vector<int> vi3({1,2,3});
  
  BOOST_CHECK(vi3.size()==3);
  BOOST_CHECK(vi3.capacity()==3);
  BOOST_CHECK(vi3.begin()!=vi3.end());
  BOOST_CHECK_NO_THROW(vi3[0]);
}

//Tests basic vector<int>() push_back
BOOST_AUTO_TEST_CASE(vector_int_push_back_test_0) {
  boost::vector<int> vi(10);
  BOOST_CHECK_NO_THROW(vi.push_back(1));
  int * x = new int(2);
  BOOST_CHECK_NO_THROW(vi.push_back(*x));
  delete x;

  for (int i=3; i<=10; i++) {
    BOOST_CHECK_NO_THROW(vi.push_back(i));
  }
  for (int i=1; i<=10; i++) {
    BOOST_CHECK(i==vi[i-1]);
  }
}

//Tests basic vector<int>() push_back strong guarantee
BOOST_AUTO_TEST_CASE(vector_int_push_back_strong_guarantee) {
  boost::vector<int> vi(1);
  BOOST_CHECK_NO_THROW(vi.push_back(1));
  BOOST_CHECK(vi[0]==1);
  BOOST_CHECK(vi.size()==1);
  BOOST_CHECK(vi.capacity()==1);
  BOOST_CHECK_THROW(vi.push_back(1), boost::exceptions::buffer_overflow);
  BOOST_CHECK(vi[0]==1);
  BOOST_CHECK(vi.size()==1);
  BOOST_CHECK(vi.capacity()==1);
  
  BOOST_CHECK_NO_THROW(vi.reserve(2));
  BOOST_CHECK(vi.size()==1);
  BOOST_CHECK(vi.capacity()==2);

  BOOST_CHECK_NO_THROW(vi.push_back(2));
  BOOST_CHECK(vi.size()==2);
  BOOST_CHECK(vi.capacity()==2);
  BOOST_CHECK(vi[0]==1);
  BOOST_CHECK(vi[1]==2);

  BOOST_CHECK_THROW(vi.push_back(2), boost::exceptions::buffer_overflow);
  BOOST_CHECK(vi.size()==2);
  BOOST_CHECK(vi.capacity()==2);
  BOOST_CHECK(vi[0]==1);
  BOOST_CHECK(vi[1]==2);
}

//tests vector<int>() pre_push_back and push_back
BOOST_AUTO_TEST_CASE(vector_int_push_back_test_watched) {
  boost::vector<int> vi(10);
  for (int i=0; i<100; i++) {
    BOOST_CHECK_NO_THROW(vi.pre_push_back());
    BOOST_CHECK_NO_THROW(vi.push_back(10));
  }
}

//tests vector<int>() Capacity functions
BOOST_AUTO_TEST_CASE(vector_int_capacity) {
  boost::vector<int> vi(10);
  BOOST_CHECK(vi.size()==0);
  BOOST_CHECK(vi.capacity()==10);
  BOOST_CHECK_NO_THROW(vi.resize(0));
  BOOST_CHECK(vi.capacity()==0);
  BOOST_CHECK(vi.size()==0);
  BOOST_CHECK_THROW(vi.push_back(1), boost::exceptions::buffer_overflow);
  BOOST_CHECK_NO_THROW(vi.resize(10));
  BOOST_CHECK(vi.capacity()==10);
  BOOST_CHECK(vi.size()==10);
  BOOST_CHECK_THROW(vi.push_back(1), boost::exceptions::buffer_overflow);
  BOOST_CHECK_NO_THROW(vi.reserve(11));
  BOOST_CHECK(vi.size()==10);
  BOOST_CHECK_NO_THROW(vi.push_back(1));
  BOOST_CHECK(vi.size()==11);
  BOOST_CHECK(vi[10]==1);
  BOOST_CHECK_NO_THROW(vi.resize(0));
  BOOST_CHECK(vi.capacity()==0);
  BOOST_CHECK(vi.size()==0);
  BOOST_CHECK_THROW(vi.push_back(0), boost::exceptions::buffer_overflow);
}



//tests vector<int>() Element Access functions
BOOST_AUTO_TEST_CASE(vector_int_element_access) {
  boost::vector<int> vi(10);
  vi.push_back(0);
  vi.push_back(1);
  vi.push_back(2);
  //test basic functionality
  BOOST_CHECK(vi.at(0)==0);
  BOOST_CHECK(vi.front()==0);
  BOOST_CHECK(vi.back()==2);
  BOOST_CHECK(vi[2]==2);
  BOOST_CHECK(vi.data()[0]==0);

  //test direct element access:
  vi[0]++;
  BOOST_CHECK(vi[0]==1);
  
  //test throws
  BOOST_CHECK_THROW(vi.at(-1), boost::exceptions::out_of_bounds);
  BOOST_CHECK_THROW(vi.at(100), boost::exceptions::out_of_bounds);
  vi.clear();
  BOOST_CHECK_THROW(vi.front(), boost::exceptions::out_of_bounds);
  BOOST_CHECK_THROW(vi.back(), boost::exceptions::out_of_bounds);
}

//tests vector<int>() Modifiers functions
BOOST_AUTO_TEST_CASE(vector_int_modifiers) {
  boost::vector<int> vi(3);
  BOOST_CHECK_NO_THROW(vi.push_back(0));
  BOOST_CHECK_NO_THROW(vi.push_back(1));
  BOOST_CHECK_NO_THROW(vi.push_back(2));
  BOOST_CHECK_THROW(vi.push_back(3), boost::exceptions::buffer_overflow);
  BOOST_CHECK_NO_THROW(vi.pre_push_back());
  BOOST_CHECK_NO_THROW(vi.push_back(3));
  BOOST_CHECK_NO_THROW(vi.pop_back());
  BOOST_CHECK(vi[2]==2);
  BOOST_CHECK_THROW(vi[3]++, boost::exceptions::out_of_bounds);
}




/*
  ==========================
  Vector<string> tests
  ==========================
*/

//Tests basic vector<string> allocation
BOOST_AUTO_TEST_CASE(vector_string_base_test_0) {
  BOOST_CHECK_NO_THROW(boost::vector<std::string> vi1);
  BOOST_CHECK_NO_THROW(boost::vector<std::string> vi2(10));
  BOOST_CHECK_NO_THROW(boost::vector<std::string> vi3({"A","BEE","SEE?!?"}));
}

//Tests basic vector<string> constructor vector<string>() and vector<string>(size_type)
BOOST_AUTO_TEST_CASE(vector_string_base_test_1) {
  boost::vector<std::string> vi;
  
  BOOST_CHECK(vi.size()==0);
  BOOST_CHECK(vi.capacity()==0);
  BOOST_CHECK(vi.begin()==vi.end());
  BOOST_CHECK_THROW(vi[0], boost::exceptions::out_of_bounds);

  boost::vector<std::string> vi2(10);
  
  BOOST_CHECK(vi2.size()==0);
  BOOST_CHECK(vi2.capacity()==10);
  BOOST_CHECK(vi2.begin()==vi2.end());
  BOOST_CHECK_THROW(vi2[0], boost::exceptions::out_of_bounds);

  boost::vector<std::string> vi3({"A","BEE","SEE?!?"});

  BOOST_CHECK(vi3.size()==3);
  BOOST_CHECK(vi3.capacity()==3);
  BOOST_CHECK(vi3.begin()!=vi3.end());
  BOOST_CHECK_NO_THROW(vi3[0]);
}

//Tests basic vector<string>() push_back
BOOST_AUTO_TEST_CASE(vector_string_push_back_test_0) {
  boost::vector<std::string> vi(10);
  BOOST_CHECK_NO_THROW(vi.push_back(std::string("GSoC15")));
  std::string * x = new std::string("BOOST RULES");
  BOOST_CHECK_NO_THROW(vi.push_back(*x));
  delete x;
  
  BOOST_CHECK(vi[0]==std::string("GSoC15"));
  BOOST_CHECK(vi[1]==std::string("BOOST RULES"));
}

//Tests basic vector<string>() push_back strong guarantee
BOOST_AUTO_TEST_CASE(vector_string_push_back_strong_guarantee) {
  boost::vector<std::string> vi(1);
  BOOST_CHECK_NO_THROW(vi.push_back("1"));
  BOOST_CHECK(vi[0]=="1");
  BOOST_CHECK(vi.size()==1);
  BOOST_CHECK(vi.capacity()==1);
  BOOST_CHECK_THROW(vi.push_back("1"), boost::exceptions::buffer_overflow);
  BOOST_CHECK(vi[0]=="1");
  BOOST_CHECK(vi.size()==1);
  BOOST_CHECK(vi.capacity()==1);
  
  BOOST_CHECK_NO_THROW(vi.reserve(2));
  BOOST_CHECK(vi.size()==1);
  BOOST_CHECK(vi.capacity()==2);

  BOOST_CHECK_NO_THROW(vi.push_back("2"));
  BOOST_CHECK(vi.size()==2);
  BOOST_CHECK(vi.capacity()==2);
  BOOST_CHECK(vi[0]=="1");
  BOOST_CHECK(vi[1]=="2");

  BOOST_CHECK_THROW(vi.push_back("2"), boost::exceptions::buffer_overflow);
  BOOST_CHECK(vi.size()==2);
  BOOST_CHECK(vi.capacity()==2);
  BOOST_CHECK(vi[0]=="1");
  BOOST_CHECK(vi[1]=="2");
}

//tests vector<string>() pre_push_back and push_back
BOOST_AUTO_TEST_CASE(vector_string_push_back_test_watched) {
  boost::vector<std::string> vi(10);
  for (int i=0; i<100; i++) {
    BOOST_CHECK_NO_THROW(vi.pre_push_back());
    BOOST_CHECK_NO_THROW(vi.push_back("a"));
  }
}

//tests vector<string>() Capacity functions
BOOST_AUTO_TEST_CASE(vector_string_capacity) {
  boost::vector<std::string> vi(10);
  BOOST_CHECK(vi.size()==0);
  BOOST_CHECK(vi.capacity()==10);
  BOOST_CHECK_NO_THROW(vi.resize(0));
  BOOST_CHECK(vi.capacity()==0);
  BOOST_CHECK(vi.size()==0);
  BOOST_CHECK_THROW(vi.push_back("1"), boost::exceptions::buffer_overflow);
  BOOST_CHECK_NO_THROW(vi.resize(10));
  BOOST_CHECK(vi.capacity()==10);
  BOOST_CHECK(vi.size()==10);
  BOOST_CHECK_THROW(vi.push_back("1"), boost::exceptions::buffer_overflow);
  BOOST_CHECK_NO_THROW(vi.reserve(11));
  BOOST_CHECK(vi.size()==10);
  BOOST_CHECK_NO_THROW(vi.push_back("1"));
  BOOST_CHECK(vi.size()==11);
  BOOST_CHECK(vi[10]=="1");
  BOOST_CHECK_NO_THROW(vi.resize(0));
  BOOST_CHECK(vi.capacity()==0);
  BOOST_CHECK(vi.size()==0);
  BOOST_CHECK_THROW(vi.push_back("0"), boost::exceptions::buffer_overflow);
}



//tests vector<string>() Element Access functions
BOOST_AUTO_TEST_CASE(vector_string_element_access) {
  boost::vector<std::string> vi(10);
  vi.push_back("0");
  vi.push_back("1");
  vi.push_back("2");
  //test basic functionality
  BOOST_CHECK(vi.at(0)=="0");
  BOOST_CHECK(vi.front()=="0");
  BOOST_CHECK(vi.back()=="2");
  BOOST_CHECK(vi[2]=="2");
  BOOST_CHECK(vi.data()[0]=="0");

  //test direct element access:
  std::string aux = " bottles of beer in the wall";
  vi[0]+= aux;
  BOOST_CHECK(vi[0]=="0" + aux);
  
  //test throws
  BOOST_CHECK_THROW(vi.at(-1), boost::exceptions::out_of_bounds);
  BOOST_CHECK_THROW(vi.at(100), boost::exceptions::out_of_bounds);
  vi.clear();
  BOOST_CHECK_THROW(vi.front(), boost::exceptions::out_of_bounds);
  BOOST_CHECK_THROW(vi.back(), boost::exceptions::out_of_bounds);
}

//tests vector<string>() Modifiers functions
BOOST_AUTO_TEST_CASE(vector_string_modifiers) {
  boost::vector<std::string> vi(3);
  BOOST_CHECK_NO_THROW(vi.push_back("0"));
  BOOST_CHECK_NO_THROW(vi.push_back("1"));
  BOOST_CHECK_NO_THROW(vi.push_back("2"));
  BOOST_CHECK_THROW(vi.push_back("3"), boost::exceptions::buffer_overflow);
  BOOST_CHECK_NO_THROW(vi.pre_push_back());
  BOOST_CHECK_NO_THROW(vi.push_back("3"));
  BOOST_CHECK_NO_THROW(vi.pop_back());
  BOOST_CHECK(vi[2]=="2");
  BOOST_CHECK_THROW(vi[3], boost::exceptions::out_of_bounds);
}
