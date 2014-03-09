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
