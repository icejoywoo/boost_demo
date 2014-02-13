/*
 * interprocess_demo.cpp
 *
 *  Created on: 2014年1月20日
 *      Author: icejoywoo
 */

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

void construct_objects(
        boost::interprocess::managed_shared_memory &managed_shm) {
	managed_shm.construct<int>("Integer")(99);
	managed_shm.construct<float>("Float")(3.14);
}

int main() {
	boost::interprocess::shared_memory_object shdmem(
	        boost::interprocess::open_or_create, "Highscore",
	        boost::interprocess::read_write);
	shdmem.truncate(1024);
	std::cout << shdmem.get_name() << std::endl;
	boost::interprocess::offset_t size;
	if (shdmem.get_size(size)) {
		std::cout << size << std::endl;
	}

	boost::interprocess::mapped_region region(shdmem,
	        boost::interprocess::read_write);
	std::cout << std::hex << "0x" << region.get_address() << std::endl;
	std::cout << std::dec << region.get_size() << std::endl;
	int *i1 = static_cast<int*>(region.get_address());
	*i1 = 99;
	boost::interprocess::mapped_region region2(shdmem,
	        boost::interprocess::read_only);
	std::cout << std::hex << "0x" << region2.get_address() << std::endl;
	std::cout << std::dec << region2.get_size() << std::endl;
	int *i2 = static_cast<int*>(region2.get_address());
	std::cout << *i2 << std::endl;

	// 即使进程终止，共享内存还会一直存在，而不论共享内存的删除是否依赖底层操作系统
	bool removed = boost::interprocess::shared_memory_object::remove(
	        "Highscore");
	std::cout << removed << std::endl;

	// 共享内存的管理, 可以根据名字查找特定的数据, 类似kv
	boost::interprocess::shared_memory_object::remove("Highscore");
	boost::interprocess::managed_shared_memory managed_shm(
	        boost::interprocess::open_or_create, "Highscore", 1024);
	// 创建数据
	int *i = managed_shm.construct<int>("Integer")(99);
	std::cout << *i << std::endl;
	// 查找数据
	std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
	if (p.first)
		std::cout << *p.first << std::endl;
	std::cout << managed_shm.destroy<int>("Integer") << std::endl; // destroy return boolean
	// destroy 由于对象如果被找到总是被删除，所以返回值 false 表示给定名称的对象没有找到
	std::pair<int*, std::size_t> p1 = managed_shm.find<int>("Integer");
	std::cout << p1.first << std::endl;

	// 创建的数据大于共享内存的容量
	try {
		boost::interprocess::shared_memory_object::remove("Highscore");
		boost::interprocess::managed_shared_memory managed_shm(
		        boost::interprocess::open_or_create, "Highscore", 1024);
		int *i = managed_shm.construct<int>("Integer")[4096](99);
		std::cout << *i << std::endl;
	} catch (boost::interprocess::bad_alloc &ex) {
		std::cerr << ex.what() << std::endl;
	}

	typedef boost::interprocess::allocator<char,
	        boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
	typedef boost::interprocess::basic_string<char, std::char_traits<char>,
	        CharAllocator> string;
	string *s = managed_shm.find_or_construct<string>("String")("Hello!",
	        managed_shm.get_segment_manager());
	s->insert(5, ", world");
	std::cout << *s << std::endl;

	// 立刻执行多个操作而不被其他应用程序的操作打断
	{
		boost::interprocess::shared_memory_object::remove("Highscore");
		boost::interprocess::managed_shared_memory managed_shm(
		        boost::interprocess::open_or_create, "Highscore", 1024);
		// managed_shm.atomic_func(boost::bind(construct_objects, boost::ref(managed_shm)));
		// std::cout << *managed_shm.find<int>("Integer").first << std::endl;
		// std::cout << *managed_shm.find<float>("Float").first << std::endl;
	}

	// 互斥
	boost::interprocess::named_mutex named_mtx(
	        boost::interprocess::open_or_create, "mtx");
	named_mtx.lock();
	++(*i);
	std::cout << *i << std::endl;
	named_mtx.unlock();
}
