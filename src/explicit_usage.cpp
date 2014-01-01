/*
 * explicit_usage.cpp
 *
 *  Created on: 2013年10月19日
 *      Author: icejoywoo
 */

#include <iostream>

class Person {
public:
	explicit Person(int age) {
		this->age = age;
	}
private:
	int age;
};

int main(int argc, char* argv[]) {
	// 不加explicit的初始化方式
	Person p1(10);
	Person *p_ptr = new Person(10);
	// Person p3 = 10; // explicit 关键字加在构造函数前，阻止隐式转换
}


