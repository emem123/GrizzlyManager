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

#include "GrizzlyHandler.h"
#include "tools/file.h"
#include <string.h>
#include "tools/macros.h"
#include <iostream>
#include <stdexcept>
#include "GrizzlyMainPageModule.h"

GrizzlyHandler::GrizzlyHandler() {
	GrizzlyMainPageModule* mainpage = new GrizzlyMainPageModule();

	registerModule(mainpage);

	/*GrizzlyModule* module = new GrizzlyModule();
	module->setName("Python");
	module->setSlug("python");
	registerModule(module);
	module = new GrizzlyModule();
	module->setName("System Info");
	module->setSlug("sysinfo");
	registerModule(module);*/

	init();

	//must be called last
	prepareHeader();
	mainpage->setModuleMap(&modules);
}

GrizzlyHandler::~GrizzlyHandler() {

}

void GrizzlyHandler::init()
{
	list<string> lines = readTextFileLines("modules.conf");
	list<string>::iterator it;

	for(it = lines.begin();it != lines.end();it++)
	{
		void* lib = dlopen(lines.front().c_str(), RTLD_LAZY);

		if (lib == NULL)
		{
			cerr << "Cannot load library: " << dlerror() << '\n';
			continue;
		}

		GrizzlyModule* (*createInstance)();
		createInstance = (GrizzlyModule* (*)()) dlsym(lib, "createInstance");

		if (createInstance == NULL)
	    {
			cerr << "Cannot create instance: " << dlerror() << '\n';
			continue;
		}

		GrizzlyModule* module = createInstance();

		if(module->getModuleName().empty() || module->getModuleSlug().empty())
		{
			printf("Name and slug of the module cannot be empty!");
		}
		registerModule(module);
	}
}

int GrizzlyHandler::onError(mg_connection* conn){
	return 0;
}

int GrizzlyHandler::onChange(mg_connection * conn){
	return 0;
}
int GrizzlyHandler::onRequest(mg_connection * conn){

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
		header += (*it).second->getModuleName();
		//Aleheader += "<div class=\"menu\">Test</div>";
		header += "</a>";
	}

	header += "</nav> <div class=\"content\">";
	footer = readTextFile("footer.html");
	error = readTextFile("error.html");
}



