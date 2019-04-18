
#include "MyTask.h"
#include "BitMap.h"
#include "Dictionary.h"
#include "CacheManager.h"
#include "Pthread.h"

#include <json/json.h>

namespace mysp
{

MyTask::MyTask(const string & queryWord, const TcpConnectionPtr & conn)
: _queryWord(queryWord)
, _conn(conn){
}

void MyTask::excute(){

	//一个线程对应一个cache,该方法的执行处于计算线程
	Cache & cache = CacheManager::getCache(atoi(pthreadName));
	string result = cache.getElement(_queryWord);
	if (result.size()){
		_conn->sendInLoop(result);
		return;
	}

	auto dict = getDict();//vector<pair<string, size_t>>
	auto index = getIndexTable();//unordered_map<string, set<int>>

	BitMap candidata(dict.size());

	//对string中的每一个字符对应索引的所有下标(set<int>)进行位图统计,存在就置1
	for (int i = 0; i != getLength(_queryWord); ++i){
		string s = getNthChar(_queryWord, i);
		auto container = index[s];
		for (int idx : container){
			candidata.setMap(idx);
		}
	}

	//对所有候选词进行编辑距离计算,将小于3的记录插入结果队列
	for (size_t idx = 0; idx != candidata.size(); ++idx){
		if (candidata.isSet(idx)){
			int dist = distance(dict[idx].first);
			if (dist <= 3){
				_resultQue.push(MyResult(
							dict[idx].first,  //word
							dict[idx].second, //freq
							dist));			  //dist
			}
		}
	}

	response();
}

void MyTask::response(){
	Json::Value item, arr;

	//将优先级队列中的结果用json数据格式封装
	for (size_t i = 0; i != 6; ++i){
		if (_resultQue.size()){
			arr.append(_resultQue.top()._word);
			_resultQue.pop();
		}else{
			break;
		}
	}
	string sendItem = arr.toStyledString();

	//缓存中存储的是:
	//query ----》 json对象 
	if (_resultQue.size())
		CacheManager::getCache(atoi(pthreadName)).addElement(_queryWord, sendItem);
	_conn->sendInLoop(sendItem);
}

int MyTask::distance(const string & rhs){
	const int size1 = getLength(_queryWord), size2 = getLength(rhs);
	if (size1 == 0)
		return size2;
	if (size2 == 0)
		return size1;

	//ed[i][j]表示 word1[0]~word1[i-1]与word2[0]~word2[j-1]之间的最小编辑距离
	vector<vector<int>> ed(size1 + 1, vector<int>(size2 + 1, 0));

	// 初始化任意字符与空字符之间的编辑距离
	for (int i = 0; i != size1 + 1; ++i)
	{
		ed[i][0] = i;
	}
	for (int i = 0; i != size2 + 1; ++i)
	{
		ed[0][i] = i;
	}

	for (int i = 1; i != size1 + 1; ++i)
	{
		for (int j = 1; j != size2 + 1; ++j)
		{
			if (getNthChar(_queryWord, i - 1) == getNthChar(rhs, j - 1))
				ed[i][j] = ed[i - 1][j - 1];
			else
				// 将3种编辑结尾的方法都尝试，取最小的结果
				ed[i][j] = min(min(ed[i][j - 1], ed[i - 1][j]), ed[i - 1][j - 1]) + 1;
		}
	}
	return ed[size1][size2];
}

string MyTask::getNthChar(const string & word, int n){
	int pos = 0;
	while (n-- ){
		pos += getBytesCode(word[pos]);
	}
	return string(word, pos, getBytesCode(word[pos]));

}
int MyTask::getLength(const string & word){
	int cnt = 0;
	for (auto cit = word.cbegin(); cit != word.cend();){
		cit += getBytesCode(*cit);
		++cnt;
	}

	return cnt;
}

int MyTask::getBytesCode(char c){
	if (!(c & 0x80)){
		return 1;	
	}
	int cnt = 0;
	do {
		c <<= 1;
		cnt ++;
	}while (c & 0x80);
	return cnt;
}

}
