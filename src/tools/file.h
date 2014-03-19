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

#ifndef FILE_H_
#define FILE_H_

#include <string>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <list>
#include <vector>
#include <map>
#include <dirent.h>
#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>

using namespace std;

namespace gz{

list<string>    getFilesInDirectory(const string &dir);
string 			readTextFile(const string &file_name);
list<string> 	readTextFileLines(const string &file_name);
vector<string> 	split(const string &src, const string &delimiters);
vector<string> 	splitWithEmpty(const string &src, const string &delimiters);
void 			vecPairToMap(map< string, string>* dst, const vector<string>* src);



/**
 * Pracovna verzia. Porovna rychlosti medzi readTextFile a tymto.
 */
static string load_text_file(std::string file_name, int code){
	std::string s;

	FILE* file = fopen(file_name.c_str(), "r");

	if(file == NULL){
		printf("Chyba pri otvarani suboru.");
		return s;
	}

	char buffer[256];
	size_t size_buffer = 256*sizeof(char);

	while(!feof(file)){
		fread(buffer,size_buffer,1,file);
		s.append(buffer);
		bzero(buffer, size_buffer);
	}

	fclose(file);
	return s;
}

};

#endif /* FILE_H_ */
