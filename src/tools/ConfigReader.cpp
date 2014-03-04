/*
 * ConfigReader.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#include "ConfigReader.h"

ConfigReader::ConfigReader() {
	// TODO Auto-generated constructor stub

}

ConfigReader::~ConfigReader() {
	// TODO Auto-generated destructor stub
}

void ConfigReader::run(const std::string &filename){

	std::ifstream stream;
	std::string line;
	stream.open(filename.c_str(),std::fstream::in);

	while(std::getline(stream,line)){

		int pos = 0;
		int initpos = 0;
/*
			list<string> itemlist;

			while(-1 != pos){
				pos = line.find_first_of(" \t", initpos);

				std::string substring = line.substr(initpos,pos-initpos+1);
				initpos = pos + 1;

				if(substring.size() != 0){
					itemlist.push_back(substring);
				}
			}
			items[itemlist.front()] = itemlist;
*/

		if(line.size() == 0)
			continue;

		initpos = line.find_first_not_of(" \t", 0);
		pos = line.find_first_of(" \t",initpos);

		if(pos == -1) // Separator not found , line has no argument, therefore is not interesting.
			continue;

		string name = line.substr(initpos,pos-initpos);
		pos = line.find_first_not_of(" \t",pos);
		string value = line.substr(pos,line.size() - pos);
		items[name] = value;

		printf("Nazov %s Hodnota:%s\n", name.c_str(), value.c_str());
	}
}
