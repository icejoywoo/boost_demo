/*
 * stl_demo.cpp
 *
 *  Created on: 2013年12月24日
 *      Author: icejoywoo
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <functional>

#include <boost/bind.hpp>

class add: public std::binary_function<int, int, void> {
public:
	void operator ()(int i, int j) const {
		std::cout << i + j << ",";
	}
};

void print(int i) {
	std::cout << i << ",";
}

bool compare(int i, int j) {
	std::cout << i << ", " << j << std::endl;
	return i < j;
}

int main() {
	std::vector<int> vec;
	for (int i = 0; i < 100; ++i)
		vec.push_back(i);
	int sum = accumulate(vec.begin(), vec.end(), 0);
	std::cout << sum << std::endl;

	std::for_each(vec.begin(), vec.end(), print);
	std::cout << std::endl;
	std::for_each(vec.begin(), vec.end(), std::bind1st(add(), 10));
	std::cout << std::endl;

	int myints[] = { 32, 71, 12, 45, 26, 80, 53, 33 };
	std::vector<int> myvector(myints, myints + 8);
	//std::sort(myvector.begin(), myvector.begin() + 4);
	//std::sort(myvector.begin() + 4, myvector.end());
	//std::sort(myvector.begin(), myvector.end(), boost::bind(compare, _2, _1));
	std::sort(myvector.begin(), myvector.end(), boost::bind(compare, _1, _2));
	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end();
	        ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	return 0;
}
