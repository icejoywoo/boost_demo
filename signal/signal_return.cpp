/*
 * signal_return.cpp
 *
 *  Created on: 2014年1月5日
 *      Author: icejoywoo
 */

#include <boost/signal.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

int func1() {
	return 1;
}

int func2() {
	return 2;
}

template<typename T>
struct min_element {
	typedef T result_type;

	template<typename InputIterator>
	T operator()(InputIterator first, InputIterator last) const {
		return *std::min_element(first, last);
	}
};

template<typename T>
struct min_element2 {
	typedef T result_type;

	template<typename InputIterator>
	T operator()(InputIterator first, InputIterator last) const {
		return T(first, last);
	}
};

int main() {
	boost::signal<int(), min_element<int> > s;
	s.connect(func1);
	s.connect(func2);
	std::cout << s() << std::endl;

	boost::signal<int(), min_element2<std::vector<int> > > s1;
	s1.connect(func1);
	s1.connect(func2);
	s1.connect(func2);
	std::vector<int> v = s1();
	std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n");
	std::cout << *std::min_element(v.begin(), v.end()) << std::endl;
}

