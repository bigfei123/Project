
#ifndef __MYSP_CACHE_H__
#define __MYSP_CACHE_H__

#include <string>
#include <set>
#include <list>
#include <unordered_map>

using namespace std;

namespace mysp
{

class Cache{
	private:
		struct CacheNode{
			string key;
			string value;

			CacheNode(string k, string v) : key(k), value(v){}
		};
	public:
	friend bool operator<(const CacheNode &, const CacheNode &);

		Cache(size_t);
		Cache(const Cache &);
		void addElement(string, string);
		string getElement(string);
		size_t size() const;

		void readFromFile(const string &);
		void writeToFile(const string &) const;
		void update(const Cache &);
		const set<CacheNode> & getRecentlySet() const;
		set<CacheNode> & getRecentlySet();
		

	private:
		size_t _capacity;
		set<CacheNode> _recentlyUpdateCache;
		list<CacheNode> _cache;
		unordered_map<string, list<CacheNode>::iterator> _hashMap;
};


}

#endif
