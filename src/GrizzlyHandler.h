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
#include <dlfcn.h>
#include <fcntl.h>

using namespace std;

class GrizzlyHandler : public MGHandler{
private:
	map<std::string, GrizzlyModule*> modules;
	string header;
	string footer;
	string error;

public:
	GrizzlyHandler();
	virtual ~GrizzlyHandler();

	void init();
	int onError(mg_connection* conn);
	int onChange(mg_connection * conn);
	int onRequest(mg_connection * conn);
	int onAuth(mg_connection* conn);

	void registerModule(GrizzlyModule* module);
	void unregisterModule(string name, bool isSlug = true);
	void prepareHeader();
};

#endif /* GRIZZLYHANDLER_H_ */
