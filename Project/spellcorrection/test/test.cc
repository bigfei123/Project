 ///
 /// @file    test.cc
 /// @author  bigfei775655478@qq.com)
 /// @date    2019-04-16 19:06:42
 ///
 
#include <json/json.h>
#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
 
void read(const string & filename)
{
	ifstream input(filename);
	if(!input) 
		cout << "open file error" << endl;

	Json::Value root, content;
	Json::Reader reader;
	Json::Value::Members mem;

	if(!reader.parse(input, root)){
		cout << "parse file error" << endl;
	}

	content = root["all"];
	mem = content.getMemberNames();
	for(auto it = mem.cbegin(); it != mem.cend(); ++it)  {
		cout << *it << endl;
	}

	input.close();
}

int main(void)
{
	read("cache");
	return 0; 
}
