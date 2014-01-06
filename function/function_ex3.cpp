/*
 * function_ex3.cpp
 *
 *  Created on: 2014年1月4日
 *      Author: icejoywoo
 */

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>

void print(boost::function<int (const char*)>& p, const char* data) {
	std::cout << p(data) << std::endl;
}

int main() {
//	std::vector<int (*)(const char*)> processors;
//	processors.push_back(std::atoi);
//	processors.push_back(reinterpret_cast<int (*)(const char*)>(std::strlen));
	std::vector<boost::function<int (const char*)> > processors;
	processors.push_back(std::atoi);
	processors.push_back(std::strlen);

	const char data[] = "1.23";

//	for (std::vector<int (*)(const char*)>::iterator it = processors.begin();
//	        it != processors.end(); ++it)
//		std::cout << (*it)(data) << std::endl;
	std::for_each(processors.begin(), processors.end(), boost::bind(print, _1, data));
}

