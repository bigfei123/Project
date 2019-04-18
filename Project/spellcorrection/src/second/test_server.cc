
#include "SpellcorrectServer.h"
#include "Configuration.h"
#include "TimerThread.h"
#include "Dictionary.h"
#include "CacheManager.h"

#include <iostream>

using namespace std;
using namespace mysp;


int main()
{

	Configuration::getInstance("/home/dafei/project/spellcorrection_stu/conf/server.conf");

	Dictionary::getInstance()->initDict(getConfig("dictName"));
	Dictionary::getInstance()->initIndex(getConfig("indexName"));

	CacheManager::initCache(atoi(getConfig("pthreadNum").c_str()));

	TimerThread timeThread(CacheManager::periodicUpdateCaches,
			atoi(getConfig("cacheUpdateInitialtime").c_str()),
			atoi(getConfig("cacheUpdateIntervaltime").c_str()));

	SpellcorrectServer server;
	timeThread.start();
	server.start();
	return 0;
}
