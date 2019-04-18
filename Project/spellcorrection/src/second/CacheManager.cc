
#include "Mylogger.h"
#include "CacheManager.h"
#include "Configuration.h"

namespace mysp
{

vector<Cache> CacheManager::_cacheList;

void CacheManager::initCache(size_t size){	
	Cache cache(atoi(getConfig("cacheCapacity").c_str()));
	cache.readFromFile(getConfig("cacheStoreFile"));
	for (size_t i = 0; i != size; ++i){
		_cacheList.push_back(cache);
	}
}

Cache & CacheManager::getCache(size_t idx){
	return _cacheList[idx];
}

void CacheManager::periodicUpdateCaches(){
	cout << "update caches" << endl;
	//把除0号cache之外的cache写入到0号cache之中，这样0号cache就会共享所有cache的内容
	for (size_t i = 1; i != _cacheList.size(); ++i){
		_cacheList[0].update(_cacheList[i]);
	}

	//再把0号cache的内容一次写入到1, 2, ..., N - 1号cache之中
	for (size_t i = 1; i != _cacheList.size(); ++i){
		_cacheList[i].update(_cacheList[0]);
	}

	for (size_t i = 0; i != _cacheList.size(); ++i){
		_cacheList[i].getRecentlySet().clear();
	}

	//还需将0号cache的内容写入到硬盘cache（文件/数据库），作为cache的备份
	_cacheList[0].writeToFile(getConfig("cacheStoreFile"));

	LogInfo("caches update success");
}

}
