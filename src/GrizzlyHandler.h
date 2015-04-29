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

#ifndef GRIZZLYHANDLER_H_
#define GRIZZLYHANDLER_H_

#include "GrizzlyModule.h"
#include "GrizzlyMainPageModule.h"
#include "GrizzlyAuthModule.h"

#include "mongoose/mongoose.h"
#include "tools/web.h"
#include "tools/file.h"
#include "tools/macros.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>

using namespace std;

class GrizzlyHandler : public GrizzlyModule::GrizzlyControl{
private:
	map<std::string, GrizzlyModule*> modules;
	GrizzlyAuthModule* authInst;
	list<void*> loadedModules;
	string header;
	string footer;
	string error;
	string style_path;
	string jquery_ui_path;
	string working_dir;
	string modules_dir;

public:
	GrizzlyHandler();
	virtual ~GrizzlyHandler();

	void setCSStyle(const string style);
	void setJQueryUI(const string ui);
	void setWorkingDir(const string dir);
	void setModulesDir(const string dir);
	void init();
	int onError(mg_connection* conn);
	int onChange(mg_connection * conn);
	int onRequest(mg_connection * conn);
	int onAuth(mg_connection* conn);
	void onExit();

	void registerModule(GrizzlyModule* module);
	void unregisterModule(string name, bool isSlug = true);
	void prepareHeader();

	string readTextFile(const string &file);
	string getDataDirectory();
};

#endif /* GRIZZLYHANDLER_H_ */
