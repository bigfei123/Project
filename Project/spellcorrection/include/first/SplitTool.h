
#ifndef __DICT_SPLITTOOL_H__
#define __DICT_SPLITTOOL_H__

#include <vector>
#include <string>

using namespace std;

namespace dict
{

class SplitTool{
	public:
		virtual ~SplitTool(){}
		virtual void cut(vector<string> &, const string &) = 0;
};

}

#endif
