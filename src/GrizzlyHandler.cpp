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


GrizzlyHandler::GrizzlyHandler() {
}

GrizzlyHandler::~GrizzlyHandler() {

}

void GrizzlyHandler::init()
{
	list<string> modNames = gz::getFilesInDirectory(modules_dir);
	list<string>::iterator it;
	GrizzlyModule* (*createInstance)();
	GrizzlyModule* module;

	for(it = modNames.begin();it != modNames.end();it++)
	{
		if((*it).substr((*it).find_last_of(".") + 1) != "so")
			continue;
		else
			(*it) = modules_dir + (*it);

		void* lib = dlopen((*it).c_str(), RTLD_LAZY);

		if (lib == NULL)
		{
			cerr << "Cannot load library: " << dlerror() << '\n';
			continue;
		}
		else
			loadedModules.push_back(lib);

		createInstance = (GrizzlyModule* (*)()) dlsym(lib, "createInstance");

		if (createInstance == NULL)
	    {
			cerr << "Cannot create instance: " << dlerror() << '\n';
			continue;
		}

		module = createInstance();

		if(module->getModuleName().empty() || module->getModuleSlug().empty())
		{
			printf("Name and slug of the module cannot be empty!\n");
			free(module);
			continue;
		}
		registerModule(module);
	}

	GrizzlyMainPageModule* mainpage = new GrizzlyMainPageModule();
	registerModule(mainpage);

	authInst = new GrizzlyAuthModule();
	authInst->setCSSPath(style_path);
	authInst->setDataPath(working_dir);

	registerModule(authInst);

	prepareHeader();
	mainpage->setModuleMap(&modules);
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
	vector<string> parsed = gz::split(conn->uri,"/");
	authInst->setCurrentConnection(conn);
	string login = authInst->getSession().login;

	try {
		if(parsed.size() == 0)
			module = modules.at("");
		else if(parsed.at(0) == "logout")
		{
			module = modules.at("");
			authInst->deleteSession();
			login = "";
		}
		else
			module = modules.at(parsed.at(0));
	}
	catch (const std::out_of_range& oor) {
		return 0; // Nenasli sme v mape co sme pozadovali...
	}

	vector<string> query;

	if(conn->query_string != NULL)
		query = gz::splitWithEmpty(conn->query_string,"=&");

	//URL decoding
	for(unsigned int i = 0;i < query.size();i++)
		query[i] = decodeURL(query[i]);

	map<string, string> parsed_query;
	gz::vecPairToMap(&parsed_query, &query);

	try{
		response = module->onRequest(&parsed_query); // Pripadna chyba je odchytena vyssie.

		if(!module->isResponseAjax()){

			if(parsed.size() == 0 || login.length() == 0)
			{
				module = modules.at("");
				response = module->onRequest(&parsed_query);
				mg_send_data(conn,response.c_str(),(response.size()+1)*sizeof(char));
			}
			else
			{
				mg_send_data(conn,header.c_str(),(header.size()+1)*sizeof(char));
				mg_send_data(conn,response.c_str(),(response.size()+1)*sizeof(char));
				mg_send_data(conn,footer.c_str(),(footer.size()+1)*sizeof(char));
			}
		}
		else{
			mg_send_data(conn,response.c_str(),(response.size()+1)*sizeof(char));
		}

	}catch(std::exception e){
		printf("[EXCEPTION] Module:\t%s\t%s\n", module->getModuleName().c_str(), e.what());
		response = error;

		if(parsed.size() == 0 || login.length() == 0)
		{
			module = modules.at("");
			response = module->onRequest(&parsed_query);
			mg_send_data(conn,response.c_str(),(response.size()+1)*sizeof(char));
		}
		else
		{
			mg_send_data(conn,header.c_str(),(header.size()+1)*sizeof(char));
			mg_send_data(conn,response.c_str(),(response.size()+1)*sizeof(char));
			mg_send_data(conn,footer.c_str(),(footer.size()+1)*sizeof(char));
		}

	}

	return MG_REQUEST_PROCESSED;
}

void GrizzlyHandler::registerModule(GrizzlyModule* module){
	module->root = this;
	module->init();
	modules[module->getModuleSlug()] = module;
}

void GrizzlyHandler::unregisterModule(string name, bool isSlug){

	if(!isSlug)
		modules.erase(name);  // Dealokuje sa spravne modul?
}

void GrizzlyHandler::onExit()
{
	list<void*>::iterator it;

	for(it = loadedModules.begin();it != loadedModules.end();it++)
	{
		dlclose((*it));
	}
}

void GrizzlyHandler::prepareHeader(){
	map<std::string, GrizzlyModule*>::iterator it;

	header = readTextFile("../data/header.html");

	int occurence = header.find("&css",0);

	if(occurence != -1)
		header.replace(occurence,4,style_path);
	occurence = header.find("&jui",0);
	if(occurence != -1)
			header.replace(occurence,4,jquery_ui_path);

	header += "<nav>";
	for(it = modules.begin(); it != modules.end(); it++){
		if((*it).second->getModuleName() != "Login")
		{
			header += "<a href=\"/";
			header += (*it).second->getModuleSlug();
			header += "\">";
			header += (*it).second->getModuleName();
			header += "</a>";
		}
	}

	header += "<a href=\"logout\" class=\"log_out\">Log out</a>";

	header += "</nav> <div class=\"content\">";
	footer = readTextFile("../data/footer.html");
	error = readTextFile("../data/error.html");
}

void GrizzlyHandler::setCSStyle(const string style){
		style_path = style;
}

void GrizzlyHandler::setJQueryUI(const string ui){
		jquery_ui_path = ui;
}

string GrizzlyHandler::readTextFile(const string &file){
	return gz::readTextFile(file);
}

string GrizzlyHandler::getDataDirectory(){
	return working_dir;
}

void GrizzlyHandler::setWorkingDir(const string dir){
	working_dir = dir;
}

void GrizzlyHandler::setModulesDir(const string dir)
{
	modules_dir = dir;
}
