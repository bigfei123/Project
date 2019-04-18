
#include "CacheManager.h"
#include "Configuration.h"
#include "SpellcorrectServer.h"
#include "MyTask.h"

using namespace std::placeholders;
#include <iostream>

namespace mysp
{

SpellcorrectServer::SpellcorrectServer()
:Server(getConfig("ip"),
		atoi(getConfig("port").c_str()),
		atoi(getConfig("listenFdNum").c_str()),
		atoi(getConfig("pthreadNum").c_str()),
		atoi(getConfig("taskQueueSize").c_str())){
}

void SpellcorrectServer::start(){
	_pthreadPool.start();
	_tcpServer.setAllCallBack(
			bind(&SpellcorrectServer::onConnection, this, _1),
			bind(&SpellcorrectServer::onMessage, this, _1),
			bind(&SpellcorrectServer::onClose, this, _1));
	_tcpServer.start();
}

void SpellcorrectServer::onConnection(const TcpConnectionPtr & conn){
		cout << conn->toString() << std::endl;
		conn->send("hello, welcome to Spellcorrect server.\r\n");
}

void SpellcorrectServer::onMessage(const TcpConnectionPtr & conn){
		std::string s(conn->receive());

		MyTask task(s, conn);
		//在IO线程中，将任务的执行交给线程池处理
		_pthreadPool.addTask(std::bind(&MyTask::excute, task));
		cout << "> add task to threadpool" << endl;
}

void SpellcorrectServer::onClose(const TcpConnectionPtr & conn){
	cout << conn->toString() << " close" << endl;
}

}
