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

	return list;
}
