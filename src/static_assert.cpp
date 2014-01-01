/*
 * static_assert.cpp
 *
 *  Created on: 2013年10月23日
 *      Author: icejoywoo
 */

#include <iostream>
#include "boost/type_traits.hpp"
#include "boost/static_assert.hpp"

template <typename T> class only_compatible_with_integral_types {
	BOOST_STATIC_ASSERT(boost::is_integral<T>::value);
};

int main() {
	only_compatible_with_integral_types<int> test2;
	std::cout << "Hello" << std::endl;
}
