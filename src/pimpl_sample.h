/*
 * pimpl_sample.h
 *
 *  Created on: 2013年10月19日
 *      Author: icejoywoo
 */

#ifndef PIMPL_SAMPLE_H_
#define PIMPL_SAMPLE_H_

#include "boost/shared_ptr.hpp"

class PimplSample {
private:
	struct impl;
	//impl* pimpl_;
	boost::shared_ptr<impl> pimpl_;
public:
	PimplSample();
	~PimplSample();
	void do_something();
};

#endif /* PIMPL_SAMPLE_H_ */
