/*
 * GrizzlyHandler.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#include "GrizzlyHandler.h"

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
	return 0;
}
