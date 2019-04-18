
#include "MyResult.h"

namespace mysp
{

bool operator<(const MyResult & r1, const MyResult & r2){
	if (r1._dist != r2._dist){
		return r1._dist > r2._dist;
	}
	if (r1._freq != r2._freq){
		return r1._freq < r2._freq;
	}

	return r1._word > r2._word;
}

}
