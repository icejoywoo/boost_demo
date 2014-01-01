/*
 * pimpl_sample.cpp
 *
 *  Created on: 2013年10月19日
 *      Author: icejoywoo
 */

#include <iostream>
#include <string>

#include "pimpl_sample.h"

struct PimplSample::impl {
	void do_something_() {
		std::cout << s_ << std::endl;
	}
	std::string s_;
};

PimplSample::PimplSample()
	: pimpl_(new impl) {
	pimpl_->s_ = "This is the pimpl idiom.";
}

PimplSample::~PimplSample() {
	//delete pimpl_; // 可能在struc impl未初始化完成的时候删除，导致无法正常析构
}

void PimplSample::do_something() {
	pimpl_->do_something_();
}

int main() {
	PimplSample pimpl;
	pimpl.do_something();
}
