
#ifndef __MYSP_MYRESULT_H__
#define __MYSP_MYRESULT_H__

#include <string>

namespace mysp
{

struct MyResult{

	MyResult(const std::string & word, size_t freq, int dist)
	: _word(word)
	, _freq(freq)
	, _dist(dist){
	}

	std::string _word;
	size_t _freq;
	int _dist;
};

bool operator<(const MyResult & r1, const MyResult & r2);

}

#endif
