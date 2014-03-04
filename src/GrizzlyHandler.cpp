/*
 * GrizzlyHandler.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#include "GrizzlyHandler.h"
#include "tools/file.h"
#include <string.h>

GrizzlyHandler::GrizzlyHandler() {
	// TODO Auto-generated constructor stub

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

	printf("Connection: %s Request method: %s\n", conn->uri, conn->request_method);


	if(strcasecmp(conn->uri,"/") == 0){
		std::string data = readTextFile("test");
		mg_send_data(conn,data.c_str(),(data.size()+1)*sizeof(char));
		for(int n=0; n < 20; n++)
			mg_printf_data(conn, "<div class=\"content\">Hello! Requested URI is [%s]  remote address %s</div>\n", conn->uri, conn->remote_ip);

		return MG_REQUEST_PROCESSED;
	}
	  //mg_write_data(conn, (void*)reply, strlen(reply));

	return 0;
}
