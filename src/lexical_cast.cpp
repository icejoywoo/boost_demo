//============================================================================
// Name        : Boost.cpp
// Author      : wujiabin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>

#include "boost/lexical_cast.hpp"

int main(void) {
	using boost::lexical_cast;
	int a = boost::lexical_cast<int>("123");
	double b = boost::lexical_cast<double>("123.1234567"); // 精度缺失
	std::cout << a << std::endl;
	std::cout << b << std::endl;

	using std::string;
	const double d = 12.13;
	std::string s = boost::lexical_cast<string>(d);
	std::cout << s << std::endl;

	int i;
	try {
		i = boost::lexical_cast<int>("abc");
	} catch(boost::bad_lexical_cast& e) {
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
