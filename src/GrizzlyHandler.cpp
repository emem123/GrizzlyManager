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

GrizzlyHandler::GrizzlyHandler() {


	GrizzlyModule* module = new GrizzlyModule();
	module->setName("Python");
	register_module(module);
	module = new GrizzlyModule();
	module->setName("System Info");
	register_module(module);
	prepareHeader();

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



	printf("Connection: %s Request method: %s Content: %s\n", conn->uri, conn->request_method, conn->content);

	if(strcasecmp(conn->uri,"/") == 0){
		//std::string data = readTextFile("test");
		mg_send_data(conn,header.c_str(),(header.size()+1)*sizeof(char));


		mg_send_data(conn,footer.c_str(),(footer.size()+1)*sizeof(char));
		//for(int n=0; n < 20; n++)
		//	mg_printf_data(conn, "<div class=\"content\">Hello! Requested URI is [%s]  remote address %s</div>\n", conn->uri, conn->remote_ip);

		return MG_REQUEST_PROCESSED;
	}
	  //mg_write_data(conn, (void*)reply, strlen(reply));

	return 0;
}

void GrizzlyHandler::register_module(GrizzlyModule* module){
			modules[module->getName()] = module;
}

void GrizzlyHandler::prepareHeader(){
	//readTextFile()
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

	header += "</nav> <div class=\"content\">ASDFSDF DF SDF";


	footer = readTextFile("footer.html");
}



