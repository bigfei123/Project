
#include "../../include/first/SplitToolCppJieba.h"
#include "../../include/first/Configuration.h"

namespace dict
{

SplitToolCppJieba::SplitToolCppJieba()
: _jieba(getConfig("dictPath"),
		getConfig("hmmPath"),
		getConfig("userDictPath"),
		getConfig("idfPath"),
		getConfig("stopWordPath")){

}

//调用cppjieba的Cut方法
void SplitToolCppJieba::cut(vector<string> & result, const string & sentence){
	_jieba.Cut(sentence, result, true);
}

}
