/*
 * function_ex1.cpp
 *
 *  Created on: 2014年1月4日
 *      Author: icejoywoo
 */

#include <algorithm>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <functional>
#include <vector>
#include <iostream>

class divide_by: public std::binary_function<int, int, int> {
public:
	int operator()(int n, int div) const {
		return n / div;
	}
};

int divide(int i, int j) {
	return i / j;
}

int main() {
	std::vector<int> numbers;
	numbers.push_back(10);
	numbers.push_back(20);
	numbers.push_back(30);

	//std::transform(numbers.begin(), numbers.end(), numbers.begin(), std::bind2nd(divide_by(), 2));
	//std::transform(numbers.begin(), numbers.end(), numbers.begin(), boost::bind(divide, _1, 2));
	std::transform(numbers.begin(), numbers.end(), numbers.begin(),
		        boost::lambda::_1 / 2);

//	for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end();
//	        ++it)
//		std::cout << *it << std::endl;
	std::for_each(numbers.begin(), numbers.end(), std::cout << boost::lambda::_1 << "\n");
}

