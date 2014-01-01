/*
 * regex.cpp
 *
 *  Created on: 2013年10月28日
 *      Author: icejoywoo
 */

#include <iostream>
#include <cassert>
#include <string>
#include "boost/regex.hpp"

class regex_callback {
	int sum_;
public:
	regex_callback() :
			sum_(0) {
	}
	template<typename T> void operator()(const T& what) {
		sum_ += atoi(what[1].str().c_str());
	}
	int sum() const {
		return sum_;
	}
};

int main() {
	boost::regex reg("(A.*)");
	std::cout
	        << boost::regex_match(
	                "This expression could match from A and beyond.", reg)
	        << std::endl;
	std::cout
	        << boost::regex_match(
	                "As this string starts with A, does it match? ", reg)
	        << std::endl;

	boost::regex reg2("\\d{3}([a-zA-Z]+).(\\d{2}|N/A)\\s\\1");
	std::string correct = "123Hello N/A Hello";
	std::string incorrect = "123Hello 12 hello";
	assert(boost::regex_match(correct, reg2) == true);
	assert(boost::regex_match(incorrect, reg2) == false);

	//regex_iterator
	boost::regex reg4("(\\d+),?");
	std::string s = "1,1,2,3,5,8,13,21";
	boost::sregex_iterator it(s.begin(), s.end(), reg4);
	boost::sregex_iterator end;
	regex_callback c;
	int sum = for_each(it, end, c).sum();
	std::cout << "sum: " << sum << std::endl;

	// 用于列举不匹配某个正则表达式的每一个字符序列,这对于分割字符串很有用
//	boost::regex reg3("/");
//	std::string s = "Split/Values/Separated/By/Slashes,";
//	std::vector<std::string> vec;
//	boost::sregex_token_iterator it(s.begin(), s.end(), reg3, -1);
//	boost::sregex_token_iterator end;
//	while (it != end)
//		vec.push_back(*it++);
//	assert(vec.size() == std::count(s.begin(), s.end(), '/') + 1);
//	assert(vec[0] == "Split");
	return 0;
}
