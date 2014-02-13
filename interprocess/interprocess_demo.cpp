/*
 * interprocess_demo.cpp
 *
 *  Created on: 2014年1月20日
 *      Author: icejoywoo
 */

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

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
}

