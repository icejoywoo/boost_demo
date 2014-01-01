/*
 * any_demo.cpp
 *
 *  Created on: 2013年11月23日
 *      Author: icejoywoo
 */

//#include <iostream>
//#include <string>
//
//#include <boost/any.hpp>
//
//int main(int argc, char* argv[]) {
//	boost::any a = std::string("A string");
//	std::string str = boost::any_cast<std::string>(a);
//	std::cout << str << std::endl;
//	double d = boost::any_cast<double>(a);
//	if (d)
//		std::cout << d << std::endl;
//	return 0;
//}

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "boost/any.hpp"
class A {
public:
	void some_function() { std::cout << "A::some_function()\n"; }
};
class B {
public:
	void some_function() { std::cout << "B::some_function()\n"; }
};
class C {
public:
	void some_function() { std::cout << "C::some_function()\n"; }
};

void print_any(boost::any& a) {
  if (A* pA=boost::any_cast<A>(&a)) {
	  pA->some_function();
  }
  else if (B* pB=boost::any_cast<B>(&a)) {
	  pB->some_function();
  }
  else if (C* pC=boost::any_cast<C>(&a)) {
	  pC->some_function();
  }else {
	  try {
		  std::cout << boost::any_cast<std::string>(a) << '\n';
	  }
	  catch(boost::bad_any_cast&) {
		  std::cout << "Oops!\n";
	  }
  }
}
int main() {
	std::cout << "Example of using any.\n\n";
	std::vector<boost::any> store_anything;
	store_anything.push_back(A());
	store_anything.push_back(B());
	store_anything.push_back(C());
	// 我们再来,再加一些别的东西
	store_anything.push_back(std::string("This is fantastic! "));
	store_anything.push_back(3);
	store_anything.push_back(std::make_pair(true, 7.92));
	void print_any(boost::any& a);
	// 稍后定义;打印a中的值
	std::for_each(
		store_anything.begin(),
		store_anything.end(),
		print_any);
}
