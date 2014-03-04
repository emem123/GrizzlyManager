/*
 * GrizzlyServer.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: visio
 */

#include "GrizzlyServer.h"

GrizzlyServer::GrizzlyServer(const char** args, const int argc) {
	// Nahratie konfigu

	server = mg_create_server(NULL);
}

GrizzlyServer::~GrizzlyServer() {
	// TODO Auto-generated destructor stub
}

GrizzlyServer* GrizzlyServer::create_server(const char** args, const int argc){

	return new GrizzlyServer(args,argc);
}

void GrizzlyServer::start(){
	//void(GrizzlyServer::*init)(void);
	//init = &GrizzlyServer::start;


	// Nacitat konfig.






	//Vytvorit server.
	setup();


}

MGHandler* GrizzlyServer::handler;
