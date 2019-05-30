
#include "../../include/first/Configuration.h"
#include "../../include/first/Mylogger.h"
#include "../../include/first/DictProducer.h"
#include "../../include/first/SplitToolCppJieba.h"
#include <iostream>
using std::cout;
using std::endl;

int main(void){
	//cout << dict::getConfig("dictionarySourceFile") << endl;
	dict::SplitToolCppJieba jieba;
	//这里传参就是使用jieba，创建中文词典;不传参是英文词典
	//dict::DictProducer dict(&jieba);
	dict::DictProducer dict;
	dict.buildDict();
	dict.buildIndex();
	dict.store();

	return 0;
}
