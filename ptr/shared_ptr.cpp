/*
 * shared_ptr.cpp
 *
 *  Created on: 2013年10月19日
 *      Author: icejoywoo
 */

#include <cassert>
#include <iostream>
#include <vector>

#include "boost/shared_ptr.hpp"

class A {
private:
	boost::shared_ptr<int> no_;
public:
	A(boost::shared_ptr<int> no) : no_(no) {}
	void value(int i) {
		*no_ = i;
	}
};

class B {
private:
	boost::shared_ptr<int> no_;
public:
	B(boost::shared_ptr<int> no) : no_(no) {}
	int value() const {
		return *no_;
	}
};

class Parent {
public:
	virtual void sing() = 0;
protected:
	virtual ~Parent() {}
};

class Child : public Parent {
public:
	virtual void sing() {
		std::cout << "do re mi fa so la" << std::endl;
	}
};

boost::shared_ptr<Parent> createParent() {
	boost::shared_ptr<Parent> p(new Child);
	return p;
}

class FileCloser {
public:
	void operator()(FILE* file) {
		std::cout << "The FileCloser has been called with a FILE*, "
				     "which will now be closed.\n";
		if (file != NULL) {
			fclose(file);
		}
	}
};

int main(int argc, char* argv[]) {
	boost::shared_ptr<int> temp(new int(14));
	A a(temp);
	B b(temp);
	a.value(20);
	assert(b.value() == 20);
	std::cout << b.value() << std::endl;

	typedef std::vector<boost::shared_ptr<Parent> > container_type;
	typedef container_type::iterator iterator;
	container_type container;
	for (int i = 0; i < 10; i++) {
		container.push_back(createParent());
	}
	std::cout << "The choir is gathered: \n";
	for (iterator iter = container.begin(); iter != container.end(); iter++) {
		(*iter)->sing();
	}

	{
		FILE* f = fopen(__FILE__,"r");
		if (f == NULL) {
			std::cerr << "Unable to open file: " << __FILE__ << std::endl;
			throw "Unable to open file.";
		}
		boost::shared_ptr<FILE> my_shared_file(f, FileCloser());
		fseek(my_shared_file.get(), 43, SEEK_SET);
		fseek(&*my_shared_file, 0, SEEK_SET);

		char temp[10240];
		fread(temp, sizeof(char), sizeof(temp), &*my_shared_file);
		std::cout << temp << std::endl;
	}
	return 0;
}
