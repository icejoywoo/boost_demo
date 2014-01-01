/*
 * addressof_demo.cpp
 *
 *  Created on: 2013年10月27日
 *      Author: icejoywoo
 */

#include <iostream>
#include <string>
#include "boost/utility.hpp"

class CodeBreaker {
public:
	int operator&() const {
		return 13;
	}
};

template <typename T> void print_address(const T& t) {
	std::cout << "Address: " << (&t) << "\n";
}

int main() {
	CodeBreaker c;
	print_address(c);
	std::string s1("abc");
	std::wstring s(L"abc");
	std::cout << "sizeof: " << sizeof(s1) << ", s1: " << s1 << std::endl;
	printf("%ls\n", s.c_str()); // wchar_t
	std::cout << "sizeof: " << sizeof(s) << ", s: " << s.c_str() << std::endl;
	std::cout << "Real Address: " << boost::addressof(c) << std::endl;
}


