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
#include <stdio.h>
#include <stdlib.h>

#define READER_BUFFER_SIZE 512

class ConfigReader {
private:
	std::map<std::string,std::string> items;

public:
	ConfigReader();
	virtual ~ConfigReader();

	size_t getItemsCount(){
		return items.size();
	}

	std::string getItemString(std::string i){
		return items[i];
	}

	int getItemInt(std::string i){
		std::string item = items[i];

		return atoi(item.c_str());
	}

	void run(const std::string &filename){
		FILE* file = fopen(filename.c_str(), "r");
		size_t size = 256;

		char* buffer2 = (char*)malloc(256*sizeof(char));
		int length = 0;

		while(!feof(file)){
			bzero(buffer2, 256);
			getline(&buffer2, &size, file);
			if((length = strlen(buffer2)) > 0 && buffer2[0] != '#'){
				//__restrictgetdelim(&buffer2,&size,' ', file)

				items["check"] = "testat";


				//for(int n = 0; n < length; n++){
				//}

			}

		}

	}

};

#endif /* CONFIGREADER_H_ */
