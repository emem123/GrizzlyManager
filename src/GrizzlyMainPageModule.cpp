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

#include "GrizzlyMainPageModule.h"

GrizzlyMainPageModule::GrizzlyMainPageModule() {
	name = "GrizzlyManager";
	slug = "main";
}

GrizzlyMainPageModule::~GrizzlyMainPageModule() {
	// TODO Auto-generated destructor stub
}

std::string GrizzlyMainPageModule::onRequest(const map<string, string>* query){

	std::map<std::string, GrizzlyModule*>::iterator it;
	std::string res;
	WebTabBuilder tabs;

	for(it = modules->begin(); it != modules->end(); it++){
		if((*it).second->getModuleName() != "Login")
		{
			res += "<div class=\"info\">";
			res += "<h3>";
			res += (*it).second->getModuleName();
			res += "</h3><span>";
			res += (*it).second->getModuleDescription();
			res += "</span></div>";
		}
	}

	tabs.addTab("Modules",res);
	tabs.addTab("Options","Under construnction.");
	tabs.addTab("Etc a ptc","Under construnction.");


	return tabs.build();// + "<textarea>Blabla</textarea><input type=\"submit\" value=\"Keke\"/>";
}
