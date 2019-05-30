
#include "Cache.h"
#include "Pthread.h"
#include "Mylogger.h"

#include <json/json.h>

#include <fstream>
#include <sstream>

namespace mysp
{

bool operator<(const Cache::CacheNode & cache1, const Cache::CacheNode & cache2){
	return cache1.key < cache2.key;
}

Cache::Cache(size_t capacity)
: _capacity(capacity){
}

Cache::Cache(const Cache & cache)
: _capacity(cache._capacity)
, _cache(cache._cache){
	for (auto it = _cache.begin(); it != _cache.end(); ++it){
		_hashMap.emplace(it->key, it);
	}
}

size_t Cache::size() const{
	return _hashMap.size();
}

string Cache::getElement(string key){
	auto it = _hashMap.find(key);
	if (it == _hashMap.end()){
		return string();
	}else {
		if (it->second != _cache.begin()){//将该cachenode插入到list的头部
			_cache.splice(_cache.begin(), _cache, it->second);
		}
		_hashMap[key] = _cache.begin();
		_recentlyUpdateCache.emplace(key, _cache.begin()->value);

		return _cache.begin()->value;
	}
}

//LRU——实现
void Cache::addElement(string key, string value){
	_recentlyUpdateCache.emplace(key, value);

	auto it = _hashMap.find(key);
	if (it == _hashMap.end()){//若在hashmap中没有查找到该记录迭代器，则添加到cache中
		_cache.emplace_front(key, value);
		if (_hashMap.size() != _capacity){
			_hashMap[key] = _cache.begin();
		}else {
			_hashMap.erase(_cache.end()->key);
			_hashMap.emplace(key, _cache.begin());
			_cache.pop_back();
		}
	}else{
		//若查找到该记录则将其更新至list头部
		it->second->value = value;
		if (it->second != _cache.begin()){
			_cache.splice(_cache.begin(), _cache, it->second);
		}
		_hashMap[key] = _cache.begin();//更新hashmap中对该记录的迭代器
	}
}

void Cache::readFromFile(const string & filename){
	ifstream input(filename);
	if (!input){
		LogWarn("Open cache file \"%s\" failed", filename.c_str());
		return;
	}else {
		LogInfo("Open cache file \"%s\" success", filename.c_str());
	}

	Json::Value root, content;
	Json::Reader reader;
	Json::Value::Members mem;

	if (!reader.parse(input, root)){
		return;
	}

	content = root["all"];
	mem = content.getMemberNames();
	for (auto cit = mem.cbegin(); cit != mem.cend(); ++cit){
		_cache.emplace_back(*cit, content[*cit].toStyledString());
		if (_cache.size() == _capacity){
			break;
		}
	}

	for (auto it = _cache.begin(); it != _cache.end(); ++it){
		_hashMap.emplace(it->key, it);
	}

	input.close();
}

void Cache::writeToFile(const string & filename) const{
	ofstream output(filename);
	if (!output){
		LogWarn("Open cache store file \"%s\" failed", filename.c_str());
		output.close();
		return;
	}else{
		LogInfo("Open cache store file \"%s\" success", filename.c_str());
	}

	Json::Value root, value, arr;
	Json::Reader reader;

	for (const auto & ele : _cache){
		if (!reader.parse(ele.value, arr)){
			LogWarn("Cannot parse Json string");
			return;
		}
		value[ele.key] = arr;
	}
	root["all"] = value;

	output << root.toStyledString();
	output.close();
}

const set<Cache::CacheNode> & Cache::getRecentlySet() const{
	return _recentlyUpdateCache;
}

set<Cache::CacheNode> & Cache::getRecentlySet(){
	return _recentlyUpdateCache;
}

void Cache::update(const Cache & cache){
	auto pairs = cache.getRecentlySet();
	for (const auto & pair : pairs ){
		addElement(pair.key, pair.value);
	}
}

}
