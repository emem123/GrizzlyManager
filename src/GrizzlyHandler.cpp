/*
 * GrizzlyHandler.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#include "GrizzlyHandler.h"
#include "tools/file.h"
#include <string.h>
#include "tools/macros.h"
#include <iostream>
#include <stdexcept>

GrizzlyHandler::GrizzlyHandler() {
	GrizzlyMainPageModule* mainpage = new GrizzlyMainPageModule();

	register_module(mainpage);

	GrizzlyModule* module = new GrizzlyModule();
	module->setName("Python");
	module->setSlug("python");
	register_module(module);
	module = new GrizzlyModule();
	module->setName("System Info");
	module->setSlug("sysinfo");
	register_module(module);
	prepareHeader();

	mainpage->setModuleMap(&modules);
}

GrizzlyHandler::~GrizzlyHandler() {
	// TODO Auto-generated destructor stub
}

int GrizzlyHandler::onError(mg_connection* conn){
	return 0;
}

int GrizzlyHandler::onChange(mg_connection * conn){
	return 0;
}
int GrizzlyHandler::onRequest(mg_connection * conn){



	printf("Connection: %s Request method: %s Content: %s\n", conn->uri, conn->request_method, conn->status_code);

	vector<string> parsed = split(conn->uri,"/");


		GrizzlyModule* module = NULL;
		printf("S1: %d\n", modules.size());

		if(parsed.size() == 0){

			module = modules.at("");

			printf("T %d\n", &modules);
		}
		else{
			try {
				module = modules.at(parsed.at(0));
			}
			catch (const std::out_of_range& oor) {
				return 0;

			}
		}
		std::string response;

		if(module != NULL){
			printf("Ttest1\n");
			response = module->onRequest("tt");
		}
		else{
			return 0;
		}

		printf("S: %d\n", modules.size());


		mg_send_data(conn,header.c_str(),(header.size()+1)*sizeof(char));
		mg_send_data(conn,response.c_str(),(response.size()+1)*sizeof(char));
		mg_send_data(conn,footer.c_str(),(footer.size()+1)*sizeof(char));
		//for(int n=0; n < 20; n++)
		//	mg_printf_data(conn, "<div class=\"content\">Hello! Requested URI is [%s]  remote address %s</div>\n", conn->uri, conn->remote_ip);

		return MG_REQUEST_PROCESSED;

	  //mg_write_data(conn, (void*)reply, strlen(reply));

	//return 0;
}

void GrizzlyHandler::register_module(GrizzlyModule* module){
			modules[module->getModuleSlug()] = module;
}

void GrizzlyHandler::prepareHeader(){
	map<std::string, GrizzlyModule*>::iterator it;

	header = readTextFile("header.html");
	header += "<nav>";
	for(it = modules.begin(); it != modules.end(); it++){
		header += "<a href=\"/";
		header += (*it).second->getModuleSlug();
		header += "\">";
		header += (*it).second->getName();
		//Aleheader += "<div class=\"menu\">Test</div>";
		header += "</a>";
	}

	header += "</nav> <div class=\"content\">";


	footer = readTextFile("footer.html");
}



