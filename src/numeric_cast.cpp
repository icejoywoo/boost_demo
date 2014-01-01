/*
 * number_cast.cpp
 *
 *  Created on: 2013年10月20日
 *      Author: icejoywoo
 */

#include <iostream>

#include "boost/cast.hpp"
#include "boost/limits.hpp"

int main() {
	std::cout << "larger_to_smaller example\n";
	long l = std::numeric_limits<short>::max();
	short s = l;
	std::cout << "s: " << s << std::endl;
	s = ++l;
	std::cout << "s: " << s << std::endl;
	try {
		l = std::numeric_limits<short>::max();
		s = boost::numeric_cast<short>(l);
		std::cout << "s: " << s << std::endl;
		s = boost::numeric_cast<short>(++l);
		std::cout << "s: " << s << std::endl;
	} catch (boost::bad_numeric_cast& e) {
		std::cerr << e.what() << std::endl;
	}
}
