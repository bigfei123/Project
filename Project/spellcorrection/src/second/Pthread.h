
#ifndef __MYSP__PTHREAD_H__
#define __MYSP__PTHREAD_H__

#include "Uncopyable.h"

#include <pthread.h>
#include <string>
#include <functional>

namespace mysp
{
//__thread的变量每一个线程有一份独立实体，各个线程的值互不干扰。
extern __thread const char * pthreadName;

class Pthread
: private Uncopyable
{
	public:
		using PthreadCallBack = std::function<void()>;

		Pthread(PthreadCallBack &&, const std::string & name = std::string());

		~Pthread();

		void start();
		void join();

		bool isRunning() const { return _isRunning; }

	private:
		static void * pthreadFunc(void *);
	private:
		pthread_t _pthid;
		std::string _name;
		bool _isRunning;
		PthreadCallBack _cb;
};

}


#endif
