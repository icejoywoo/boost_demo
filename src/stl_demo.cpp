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

int main() {
	std::vector<int> vec;
	for (int i = 0; i < 100; ++i)
		vec.push_back(i);
	int sum = accumulate(vec.begin(), vec.end(), 0);
	std::cout << sum << std::endl;
	return 0;
}
