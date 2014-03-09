/*
 * file.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#include "file.h"

string readTextFile(const string &file_name){
	std::ifstream stream;
	std::string line;
	string ret_string;
	stream.open(file_name.c_str(),std::fstream::in);

	while(getline(stream, line)){
		ret_string.append(line);
	}

	stream.close();

	return ret_string;
}

list<string> readTextFileLines(const string &file_name){
	std::ifstream stream;
	list<string> list;
	std::string line;
	stream.open(file_name.c_str(),std::fstream::in);

	while(getline(stream, line)){
		list.push_back(line);
	}

	stream.close();

	return list;
}

vector<string> split(const string &src, const string &delimiters){
	vector<string> list;
	string substr;

	int p = 0;
	int s = 0;

	p = src.find_first_of(delimiters,s);

	while(p != -1){
		if(s != p){
			list.push_back(src.substr(s,p-s));
		}

		s = p + 1;
		p = src.find_first_of(delimiters,s);
	}



	if(s < src.size()){
		list.push_back(src.substr(s));
	}

	return list;
}

vector<string> splitWithEmpty(const string &src, const string &delimiters){
	vector<string> list;
	string substr;

	int p = 0;
	int s = 0;

	p = src.find_first_of(delimiters,s);

	while(p != -1){
		if(s != p){
			list.push_back(src.substr(s,p-s));
		}
		else
			list.push_back("");

		s = p + 1;
		p = src.find_first_of(delimiters,s);
	}



	if(s < src.size()){
		list.push_back(src.substr(s));
	}

	return list;
}

void vecPairToMap(map< string, string>* dst, const vector<string>* src){
	if(src->size() % 2 != 0)
		return;

	string key;
	string value;

	vector<string>::const_iterator it = src->begin();


	for(;it != src->end();it++){
		key = (*it);
		it++;
		value = (*it);
		(*dst)[key] = value;
	}
}

