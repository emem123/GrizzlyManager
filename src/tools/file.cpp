/*
C++ server for web-driven administration with module support.
Copyright (C) 2014  Vladimír Bartošík, Martin Kuzma, Marek Moravčík

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

