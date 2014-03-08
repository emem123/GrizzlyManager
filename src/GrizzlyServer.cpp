/*
 * GrizzlyServer.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: visio
 */

#include "GrizzlyServer.h"
#include "tools/file.h"

GrizzlyServer::GrizzlyServer(const char** args, const int argc) {
	// Nahratie konfigu
	handler = new GrizzlyHandler();
	server = mg_create_server(NULL);
}

GrizzlyServer::~GrizzlyServer() {
	// TODO Auto-generated destructor stub
}

GrizzlyServer* GrizzlyServer::create_server(const char** args, const int argc){

	/*
	list<string> l = readTextFileLines("test");
	list<string>::iterator it;

	for(it = l.begin(); it != l.end(); it++){
		printf("Nacitany riadok: %s\n",(*it).c_str());
	}
	*/

	return new GrizzlyServer(args,argc);
}

int GrizzlyServer::start(){

	ConfigReader config;
	//reader.run("config");
	ConfigReader modules;

	//modules.run("modules");

	mg_set_option(server, "document_root", ".");
	mg_set_option(server, "listening_port", "80");

	setup();

	for (;;) mg_poll_server(server, 1000); // main loop

	mg_destroy_server(&server);

	return 0;
}

MGHandler* GrizzlyServer::handler;
