/*
 * file.h
 *
 *	Zakaz pouzivania bez suhlasu.
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
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

using namespace std;


string 			readTextFile(const string &file_name);
list<string> 	readTextFileLines(const string &file_name);
vector<string> 	split(const string &src, const string &delimiters);
vector<string> 	splitWithEmpty(const string &src, const string &delimiters);
void vecPairToMap(map< string, string>* dst, const vector<string>* src);
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

	return s;
}

#endif /* FILE_H_ */
