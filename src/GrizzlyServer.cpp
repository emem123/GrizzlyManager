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
