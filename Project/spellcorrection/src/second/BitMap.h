
#ifndef __MYSP_BITMAP_H__
#define __MYSP_BITMAP_H__

#include <vector>
using namespace std;

namespace mysp
{

class BitMap{
	public:
		BitMap(const size_t);

		bool isSet(const size_t) const;
		void setMap(const size_t);
		size_t size() const;
	private:
		size_t _size;
		vector<char> _bitmap;
};

}

#endif
