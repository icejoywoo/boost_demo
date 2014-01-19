/*
 * thread_demo.cpp
 *
 *  Created on: 2014年1月6日
 *      Author: icejoywoo
 */

#include <boost/thread.hpp>
//#include <boost/thread/mutex.hpp>
#include <iostream>

void wait(int seconds) {
	boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

//boost::recursive_mutex mut;
//boost::mutex mutex;
boost::timed_mutex mutex;

void thread() {
	try {
		for (int i = 0; i < 5; ++i) {
			//wait(1); // 没有sleep, 无法出发interrupt
			//boost::mutex::scoped_lock lock(mutex);
//			boost::lock_guard<boost::mutex> lock(mutex);
//			std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl;
			boost::unique_lock<boost::timed_mutex> lock(mutex,
			        boost::try_to_lock);
			if (!lock.owns_lock())
				lock.timed_lock(
				        boost::get_system_time()
				                + boost::posix_time::seconds(1));
			std::cout << "Thread " << boost::this_thread::get_id() << ": " << i
			        << std::endl;
			boost::timed_mutex *m = lock.release();
			m->unlock();
		}
	} catch (boost::thread_interrupted&) {
	}
}

int main() {
	std::cout << boost::this_thread::get_id() << std::endl;
	std::cout << boost::thread::hardware_concurrency() << std::endl;
	boost::thread t1(thread);
	boost::thread t2(thread);
	//wait(3);
	//t1.interrupt();
	t1.join();
	t2.join();
	return 0;
}
