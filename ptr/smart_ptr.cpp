/*
 * smart_ptr.cpp
 *
 *  Created on: 2013年10月19日
 *      Author: icejoywoo
 */

#include <algorithm>
#include <cstdio>
#include <string>

//#include "boost/scoped_ptr.hpp"
//#include "boost/shared_ptr.hpp"
// 包含其他ptr
#include "boost/smart_ptr.hpp"
#include "boost/noncopyable.hpp"

class Foo: public boost::noncopyable {
public:
	explicit Foo() {}
	virtual ~Foo() { std::cout << "destroy foo." << std::endl;}
	operator bool() const {
		return false;
	}
};

int main(int argc, char* argv[]) {
	int* pInt = new int[100];
	boost::shared_ptr<int> sp1(pInt);
	printf("sp1 use_count: %ld\n", sp1.use_count());

	// boost::shared_ptr<int> sp2(pInt); // 错误用法, 导致malloc错误
	boost::shared_ptr<int> sp2(sp1);
	printf("sp2 use_count: %ld\n", sp2.use_count());

	// scoped_ptr
	{
		boost::scoped_ptr<std::string> p(
		        new std::string("Use scoped_ptr often"));
		if (p) {
			std::cout << *p << std::endl;
		}
		size_t len = p->size();
		std::cout << len << std::endl;
		*p = "Change scoped_ptr.";
		if (p) {
			std::cout << *p << std::endl;
		}
	} // exit the scope, destroy the scoped_ptr

	{
		boost::scoped_ptr<std::string> p(NULL); // null-pointer 空指针
		std::cout << p.get() << " test" << std::endl;
	} // exit the scope, destroy the scoped_ptr

	// scoped_ptr 不可以复制 noncopyable
	{
		boost::scoped_ptr<std::string> p_scoped(new std::string("Hello"));
		std::auto_ptr<std::string> p_auto(new std::string("Hello"));
		p_scoped->size();
		p_auto->size();
		//boost::scoped_ptr<std::string> p_another_scoped = p_scoped; // scoped_ptr 不可以复制
		std::auto_ptr<std::string> p_another_auto = p_auto;
		p_another_auto->size();
		// (*p_auto).size(); // auto_ptr 复制操作转移了指针控制权，原来的变为null，出错
	}

	// 不推荐使用, 只是为了兼容旧式的c风格代码, 推荐使用std::vector, 功能有限
	int* array = new int[100];
	boost::scoped_array<int> sa(array);
	std::fill_n(&array[0], 100, 5);
	sa[30] = sa[10] + sa[20];
	std::cout << sa[30] << std::endl;

//	Foo f;
//	if (f) {
//		std::cout << sa[30] << std::endl;
//	}

	{
		boost::shared_ptr<Foo> f1(new Foo);
		boost::shared_ptr<Foo> f2 = f1;
		std::cout << "count: " << f1.use_count() << std::endl;
		std::cout << "count: " << f2.use_count() << std::endl;
	}

	return 0;
}
