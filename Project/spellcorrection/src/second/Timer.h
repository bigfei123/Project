
#ifndef __MYSP_TIMER_H__
#define __MYSP_TIMER_H__

#include <functional>

namespace mysp
{

class Timer{
	public:
		using TimerCallBack = std::function<void()>;
		Timer(int, int, TimerCallBack);
		~Timer();
		void start();
		void stop();
	private:
		int createTimerfd();
		void setTimerfd(int, int);
		void handleRead();
	private:
		int _timerfd;
		int _initialTime;
		int _intervalTime;
		bool _isStarted;
		TimerCallBack _cb;
};

}

#endif
