/*
 * ConfigReader.h
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

#include <map>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

struct config_pair_s{
	string name;
	string value;
};

class ConfigReader {
private:


public:
	map<string,std::string > items;

	ConfigReader();
	virtual ~ConfigReader();

	size_t getItemsCount(){
		return items.size();
	}

	string getItemArgs(std::string i){
		return items[i];
	}

	/*
	int getItemInt(std::string i){
		std::string item = items[i];
		return atoi(item.c_str());
	}*/

	void run(const std::string &filename, bool print = false);

};

#endif /* CONFIGREADER_H_ */
