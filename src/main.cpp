/*
 * main.cpp
 *
 *  Created on: Mar 1, 2014
 *      Author: visio
 */
#include <stdio.h>
#include "mongoose/mongoose.h"
#include <string.h>
#include <string>

#include "GrizzlyServer.h"
#include "tools/ConfigReader.h"

static int handle_auth(struct mg_connection *conn){

	return MG_REQUEST_PROCESSED;

}

std::string load_text_file(std::string file_name, int code){
	std::string s;

	FILE* file = fopen(file_name.c_str(), "r");

	if(file == NULL){
		printf("Chyba pri otvarani suboru.");
	}

	char buffer[256];
	size_t size_buffer = 256*sizeof(char);

	while(!feof(file)){
		fread(buffer,size_buffer,1,file);
		s.append(buffer);
		bzero(buffer, size_buffer);
	}

	return s;
}

static int handle_hello(struct mg_connection *conn) {
  static const char *reply = "Hello world!\n";

  printf("Connection: %s Request method: %s\n", conn->uri, conn->request_method);

  //conn->

  if(strcasecmp(conn->uri,"/test2") == 0){
	  std::string data = load_text_file("test",0);
	  mg_send_data(conn,data.c_str(),(data.size()+1)*sizeof(char));

	  for(int n=0; n < 20; n++)
		  mg_printf_data(conn, "<div class=\"content\">Hello! Requested URI is [%s]  remote address %s</div>\n", conn->uri, conn->remote_ip);

	  return MG_REQUEST_PROCESSED;
  }
  //mg_write_data(conn, (void*)reply, strlen(reply));
  return 0;
}

int main(const char** args, int argc){

	//GrizzlyServer* gserver = GrizzlyServer::create_server(args, argc);

	ConfigReader reader;

	reader.run("d");

	std::string st = load_text_file("/proc/meminfo",0);


	printf("%s\n", st.c_str());

	mg_server* server = mg_create_server(NULL);

	mg_set_option(server, "document_root", ".");
	mg_set_option(server, "listening_port", "180");
	mg_set_request_handler(server, &handle_hello);

	mg_set_auth_handler(server,&handle_auth);
	//mg_add_uri_handler(server, "/hello", &handle_hello);

	for (;;) mg_poll_server(server, 1000);
	mg_destroy_server(&server);
	return 0;
}


