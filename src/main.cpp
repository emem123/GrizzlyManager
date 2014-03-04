/*
 * main.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: visio
 */

#include "GrizzlyServer.h"

/*
std::string load_text_file(std::string file_name, int code){
	std::string s;

	FILE* file = fopen(file_name.c_str(), "r");

	if(file == NULL){
		printf("Chyba pri otvarani suboru.");
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
*/

int main( int argc, const char** args){
	GrizzlyServer* gserver = GrizzlyServer::create_server(args, argc);
	return gserver->start();
}


