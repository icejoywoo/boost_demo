/*
 * bind_demo.cpp
 *
 *  Created on: 2014年1月4日
 *      Author: icejoywoo
 */

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lambda/if.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

void add(int i, int j, std::ostream &os) {
	os << i + j << std::endl;
}

class world {
public:
	void hello(std::ostream &os) {
		os << "Hello, world!" << std::endl;
	}
};

int main() {
	std::vector<int> v;
	v.push_back(1);
	v.push_back(3);
	v.push_back(2);

	std::for_each(v.begin(), v.end(),
	        boost::bind(add, 10, _1, boost::ref(std::cout)));

	std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n");
	std::for_each(v.begin(), v.end(),
			boost::lambda::if_then(boost::lambda::_1 > 1, std::cout << boost::lambda::_1 << "\n"));

	boost::function<int(const char*)> f = std::atoi;
	std::cout << f("1609") << std::endl;
	f = std::strlen;
	std::cout << f("1609") << std::endl;
	try {
		boost::function<int(const char*)> f;
		f("");
	} catch (boost::bad_function_call &ex) {
		std::cout << ex.what() << std::endl;
	}

	boost::function<void (world*, std::ostream&)> f1 = &world::hello;
	world w;
	f1(&w, boost::ref(std::cout));
}

