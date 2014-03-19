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

#ifndef GRIZZLYSERVER_H_
#define GRIZZLYSERVER_H_

#include "mongoose/mongoose.h"
#include "tools/ConfigReader.h"
#include "GrizzlyHandler.h"
#include <string>

class GrizzlyServer {
private:
	mg_server* server;
	int port;				// Port we are using.
	std::string root_path; 	// Root document path

	map<std::string, GrizzlyModule*> modules;
	static GrizzlyHandler* handler;

	static int handle_request(mg_connection* conn){
		return GrizzlyServer::handler->onRequest(conn);
	}


	static int handle_error(mg_connection* conn){
		return GrizzlyServer::handler->onError(conn);
	}

	void setup();

public:
	GrizzlyServer(const char** args, const int argc);
	virtual ~GrizzlyServer();
	static GrizzlyServer* create_server(const char** args, const int argc);
	int start();
};

#endif /* GRIZZLYSERVER_H_ */
