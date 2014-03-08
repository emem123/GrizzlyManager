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

	registerModule(mainpage);

	GrizzlyModule* module = new GrizzlyModule();
	module->setName("Python");
	module->setSlug("python");
	registerModule(module);
	module = new GrizzlyModule();
	module->setName("System Info");
	module->setSlug("sysinfo");
	registerModule(module);
	prepareHeader();

	mainpage->setModuleMap(&modules);
}

GrizzlyHandler::~GrizzlyHandler() {

}

int GrizzlyHandler::onError(mg_connection* conn){
	return 0;
}

int GrizzlyHandler::onChange(mg_connection * conn){
	return 0;
}
int GrizzlyHandler::onRequest(mg_connection * conn){
	//printf("Connection: %s \nRequest method: %s \nContent: %s\n\n", conn->uri, conn->query_string, conn->connection_param);
	GrizzlyModule* module = NULL;
	std::string response;
	vector<string> parsed = split(conn->uri,"/");

	try {
		if(parsed.size() == 0)
			module = modules.at("");
		else
			module = modules.at(parsed.at(0));
	}
	catch (const std::out_of_range& oor) {
		return 0; // Nenasli sme v mape co sme pozadovali...
	}

	vector<string> query;

	if(conn->query_string != NULL)
		query = splitWithEmpty(conn->query_string,"=&");

	map<string, string> parsed_query;
	vecPairToMap(&parsed_query, &query);


	try{
		response = module->onRequest(&parsed_query); // Pripadna chyba je odchytena vyssie.
	}catch(std::exception e){
		printf("[EXCEPTION] Module:\t%s\t%s\n", module->getModuleName().c_str(), e.what());
		response = error;
	}

	mg_send_data(conn,header.c_str(),(header.size()+1)*sizeof(char));
	mg_send_data(conn,response.c_str(),(response.size()+1)*sizeof(char));
	mg_send_data(conn,footer.c_str(),(footer.size()+1)*sizeof(char));

	return MG_REQUEST_PROCESSED;
}

void GrizzlyHandler::registerModule(GrizzlyModule* module){
			modules[module->getModuleSlug()] = module;
}

void GrizzlyHandler::unregisterModule(string name, bool isSlug){

	if(!isSlug)
		modules.erase(name);  // Dealokuje sa spravne modul?
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
	error = readTextFile("error.html");
}



