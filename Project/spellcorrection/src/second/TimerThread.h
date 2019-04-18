
#ifndef __MYSP_TIMERTHREAD_H__
#define __MYSP_TIMERTHREAD_H__

#include "Pthread.h"
#include "Timer.h"

namespace mysp
{

class TimerThread{
	public:
		using TimerCallBack = Timer::TimerCallBack;
		TimerThread(TimerCallBack && cb, int intitalTime, int intervalTime);
		void start();
		void stop();
	private:
		Timer _timer;
		Pthread _thread;
};

}

#endif
