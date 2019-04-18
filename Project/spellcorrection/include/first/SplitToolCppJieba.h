
#ifndef __DICT_SPLITTOOLCPPJIEBA_H__
#define __DICT_SPLITTOOLCPPJIEBA_H__

#include "SplitTool.h"
#include "../../libs/cppjieba/include/cppjieba/Jieba.hpp"

namespace dict
{

class SplitToolCppJieba
: public SplitTool{
	public:
		SplitToolCppJieba();
		void cut(vector<string> &, const string &);
	private:
		cppjieba::Jieba _jieba;
};

}

#endif
