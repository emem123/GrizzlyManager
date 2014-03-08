/*
 * GrizzlyHandler.h
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#ifndef GRIZZLYHANDLER_H_
#define GRIZZLYHANDLER_H_

#include "mongoose/MGHandler.h"
#include "GrizzlyModule.h"
#include "GrizzlyMainPageModule.h"

#include <string>
#include <map>
#include <unistd.h>

using namespace std;

class GrizzlyHandler : public MGHandler{
private:
	map<std::string, GrizzlyModule*> modules;
	string header;
	string footer;

public:
	GrizzlyHandler();
	virtual ~GrizzlyHandler();

	int onError(mg_connection* conn);
	int onChange(mg_connection * conn);
	int onRequest(mg_connection * conn);
	int onAuth(mg_connection* conn);

	void register_module(GrizzlyModule* module);
	void prepareHeader();
};

#endif /* GRIZZLYHANDLER_H_ */
