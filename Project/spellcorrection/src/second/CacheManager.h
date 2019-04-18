
#ifndef __MYSP_CACHEMANAGER_H__
#define __MYSP_CACHEMANAGER_H__

#include <vector>
#include "Cache.h"

namespace mysp
{

class CacheManager{
	public:
		static void initCache(size_t);
		static Cache & getCache(size_t);
		static void periodicUpdateCaches();
	private:
		static vector<Cache> _cacheList;
};

}

#endif
