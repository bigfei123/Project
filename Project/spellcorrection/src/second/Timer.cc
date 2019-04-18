
#include "Timer.h"
#include "Mylogger.h"

#include <poll.h>
#include <unistd.h>
#include <sys/timerfd.h>

namespace mysp
{

Timer::Timer(int initialTime, int intervalTime, TimerCallBack cb)
: _timerfd(createTimerfd())
, _initialTime(initialTime)
, _intervalTime(intervalTime)
, _isStarted(false)
, _cb(cb){
}

Timer::~Timer(){
	if (_isStarted)
		stop();
}

void Timer::start(){
	_isStarted = true;
	//添加到epoll读
	setTimerfd(_initialTime, _intervalTime);
	struct pollfd pfd;
	pfd.fd = _timerfd;
	pfd.events = POLLIN;

	while(_isStarted)
	{
		int nready = ::poll(&pfd, 1, 50000);
		if(nready == -1 && errno == EINTR)
			continue;
		else if(nready == -1) {
			LogError("poll error");
			exit(EXIT_FAILURE);
		} else if(nready == 0) 
			printf(">>> timer has timeout!!\n\n");
		else {
			if(pfd.revents & POLLIN) {
				handleRead();//处理读事件
				if(_cb) _cb();//执行任务
			}
		}
	}
}

void Timer::stop(){
	if (_isStarted){
		_isStarted = false;
		setTimerfd(0, 0);
	}
}

int Timer::createTimerfd(){
	int fd = timerfd_create(CLOCK_REALTIME, 0);
	if (fd == -1){
		LogError("timerfd_create error");
	}
	return fd;
}

void Timer::setTimerfd(int initialTime, int intervalTime){
	struct itimerspec value = {{intervalTime, 0},
		{initialTime, 0}
	};

	if (-1 == timerfd_settime(_timerfd, 0, &value, NULL)){
		LogError("timerfd_settime error");
	}
}

void Timer::handleRead(){
	uint64_t u;

	if (sizeof(u) != read(_timerfd, &u, sizeof(u))){
		LogError("read error");
	}
}

}
