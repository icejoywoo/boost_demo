/*
 * function_ex2.cpp
 *
 *  Created on: 2014年1月4日
 *      Author: icejoywoo
 */

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <string>
#include <vector>
#include <iostream>

void add_size(std::string& it, std::vector<int>& sizes) {
	sizes.push_back(it.size());
}

int main() {
	std::vector<std::string> strings;
	strings.push_back("Boost");
	strings.push_back("C++");
	strings.push_back("Libraries");

	std::vector<int> sizes;

//	for (std::vector<std::string>::iterator it = strings.begin();
//	        it != strings.end(); ++it)
//		sizes.push_back(it->size());
	std::for_each(strings.begin(), strings.end(), boost::bind(add_size, _1, boost::ref(sizes)));

//	for (std::vector<int>::iterator it = sizes.begin(); it != sizes.end(); ++it)
//		std::cout << *it << std::endl;
	std::for_each(sizes.begin(), sizes.end(), std::cout << boost::lambda::_1 << "\n");
}

