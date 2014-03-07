/*
 * GrizzlyServer.h
 *
 *  Created on: Mar 1, 2014
 *      Author: visio
 */

#ifndef GRIZZLYSERVER_H_
#define GRIZZLYSERVER_H_

#include "mongoose/mongoose.h"
#include "mongoose/MGHandler.h"
#include "tools/ConfigReader.h"
#include "GrizzlyHandler.h"
#include <string>

class GrizzlyServer {
private:
	mg_server* server;
	int port;				// Port we are using.
	std::string root_path; 	// Root document path

	map<std::string, GrizzlyModule*> modules;

	static MGHandler* handler;

	static int handle_request(mg_connection* conn){
		return GrizzlyServer::handler->onRequest(conn);
	}

	static int handle_error(mg_connection* conn){
		return GrizzlyServer::handler->onError(conn);
	}

	void setup(){
		mg_set_http_error_handler(server,&GrizzlyServer::handle_error);
		mg_set_request_handler(server,&GrizzlyServer::handle_request);
	}




public:
	GrizzlyServer(const char** args, const int argc);
	virtual ~GrizzlyServer();
	static GrizzlyServer* create_server(const char** args, const int argc);

	int start();

};

#endif /* GRIZZLYSERVER_H_ */
