
#include "Mylogger.h"
#include "Dictionary.h"

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>

using namespace std;

namespace mysp
{

Dictionary::AutoRelease Dictionary::_ar;
Dictionary * Dictionary::_pInstance = getInstance();

Dictionary::AutoRelease::~AutoRelease(){
	if(_pInstance){
		delete _pInstance;
	}
}

Dictionary * Dictionary::getInstance(){
	if (!_pInstance){
		_pInstance = new Dictionary();
	}

	return _pInstance;
}

void Dictionary::initDict(const string & path){
	string dictFile = path;
	if (dictFile.size() == 0){
		LogError("No dictionary file");
		exit(EXIT_FAILURE);
	}

	ifstream input(dictFile);
	if (!input){
		LogError("Open dictionary file \"%s\" failed", dictFile.c_str());
		exit(EXIT_FAILURE);
	}else {
		LogInfo("Open dictionary file \"%s\", success", dictFile.c_str());
	}

	string line, word, strCnt;
	while (getline(input, line)){
		istringstream ss(line);

		ss >> word;
		ss >> strCnt;
		_dict.emplace_back(word, ::atol(strCnt.c_str()));
	}
	input.close();
}

void Dictionary::initIndex(const string & path){
	string indexFile = path;
	if (indexFile.size() == 0){
		LogError("No index file");
		exit(EXIT_FAILURE);
	}

	ifstream input(indexFile);
	if (!input){
		LogError("Open index file \"%s\" failed", indexFile.c_str());
		exit(EXIT_FAILURE);
	}else {
		LogInfo("Open index file \"%s\", success", indexFile.c_str());
	}

	string line;
	vector<string> vec;
	while (getline(input, line)){
		boost::split(vec, line, boost::is_any_of(" :"), boost::token_compress_on);
		for (auto cit = vec.cbegin() + 1; cit != vec.end(); ++cit){
			_indexTable[vec[0]].insert(atol(cit->c_str()));
		}
	}
	input.close();
}

}
