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

#ifndef GRIZZLYMAINPAGEMODULE_H_
#define GRIZZLYMAINPAGEMODULE_H_
#include "GrizzlyModule.h"
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include "webtools/WebTabBuilder.h"

class GrizzlyMainPageModule : public GrizzlyModule {
private:
	std::map<std::string, GrizzlyModule*>* modules;


public:
	GrizzlyMainPageModule();
	virtual ~GrizzlyMainPageModule();

	std::string getModuleDescription(){ return "This is core module for GrizzlyManager. It's purpose is to show this page.";}

	void setModuleMap(std::map<std::string, GrizzlyModule*>* mods){
		modules = mods;
	}

	std::string onRequest(const map<string, string>* query);

	void init(){}

};

#endif /* GRIZZLYMAINPAGEMODULE_H_ */
