/*
 * polymorphic_case.cpp
 *
 *  Created on: 2013年10月20日
 *      Author: icejoywoo
 */

#include <iostream>
#include <string>

#include "boost/cast.hpp"

class Base1 {
public:
	virtual void print() const {
		std::cout << "Base1::print\n";
	}
	virtual ~Base1() {}
};

class Base2 {
public:
	virtual void only_base2() const {
		std::cout << "Base1::only_base2\n";
	}
	virtual ~Base2() {}
};

class Derived : public Base1, public Base2 {
public:
	void print() {
		std::cout << "derived::print()\n";
	}
	void only_here() {
		std::cout << "derived::only_here()\n";
	}
	void only_base2() {
		std::cout << "Oops, here too!\n";
	}
};

int main() {
	Base1* p1 = new Derived;
	p1->print();
	try {
		Derived* pD = boost::polymorphic_cast<Derived*>(p1);
		pD->only_here();
		pD->only_base2();
		Base2* pB = boost::polymorphic_cast<Base2*>(p1);
		pB->only_base2();
	} catch (std::bad_cast& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
