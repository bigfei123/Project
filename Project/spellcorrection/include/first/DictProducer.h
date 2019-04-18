
#ifndef __DICT_DICTPRODUCCER_H__
#define __DICT_DICTPRODUCCER_H__

#include "SplitTool.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>

namespace dict
{

class Configuration;

class DictProducer{
	public:
		DictProducer();
		DictProducer(SplitTool * splitTool);
		void buildDict();
		void buildIndex();
		void store() const;

	private:
		void getStopWordsDict(const string &);
		void getFiles();
		void strProcess(std::string & );
		int getBytesCode(char);

	private:
		std::string _dir;				//字典源文件目录
		std::vector<std::string> _files;//所有字典源文件
		SplitTool * _splitTool;			//分词工具对象指针,英文时为NULL
		std::unordered_set<std::string> _stopWordsDict;//停用词词典
		std::unordered_map<std::string, size_t> _dict; //词典
		std::unordered_map<std::string, std::set<size_t>> _index;//索引
};

}

#endif
