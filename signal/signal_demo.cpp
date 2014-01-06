/*
 * signal_demo.cpp
 *
 *  Created on: 2014年1月5日
 *      Author: icejoywoo
 */

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/signal.hpp>
#include <iostream>
#include <memory>

void func() {
	std::cout << "Hello, world!" << std::endl;
}

void func1() {
	std::cout << "Hello" << std::flush;
}

void func2() {
	std::cout << ", world!" << std::endl;
}

class world
{
  public:
    void hello() const
    {
      std::cout << "Hello, world!" << std::endl;
    }
};

int main() {
	boost::signal<void()> s;
//	s.connect(func);
	boost::signals::connection c = s.connect(func);
	{
		boost::signals::scoped_connection c = s.connect(func);
	}
	c.block();
	s();
	c.unblock();
//	c.disconnect();
	s();

//	boost::function<void()> f;
//	f = func;
//	f();
//
//	boost::signal<void()> s1;
//	s1.connect(func1);
//	s1.connect(func2);
//	//s1.disconnect(func2);
//	std::cout << s1.num_slots() << std::endl;
//	if (!s1.empty())
//		s1();
//	s1.disconnect_all_slots();
//
//	boost::signal<void()> s2;
//	s2.connect(1, func2);
//	s2.connect(0, func1);
//	s2();

	boost::signal<void()> s3;
	{
		std::auto_ptr<world> w(new world());
		//s3.connect(boost::bind(&world::hello, w.get()));
		boost::signals::scoped_connection c = s3.connect(boost::bind(&world::hello, w.get()));
	}
	std::cout << s3.num_slots() << std::endl;
	s3();
}

