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

#ifndef GRIZZLYMODULE_H_
#define GRIZZLYMODULE_H_

#include <dlfcn.h>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

using namespace std;

class GrizzlyModule {
protected:
	std::string name;
	std::string slug;


public:
	GrizzlyModule();
	virtual ~GrizzlyModule();

	//std::string getName(){return name;}
	void setName(const std::string &arg){ name = arg;}
	void setSlug(const std::string &arg){ slug = arg;}
	virtual std::string getModuleName(){ return name;}
	virtual std::string getModuleSlug(){ return slug;}
	virtual std::string getModuleDescription(){ return "This module does nothing.";}

	virtual std::string onRequest(const map<string,string>* query) = 0;

	virtual void init(){ }
	virtual void resolve(){ }

};

#endif /* GRIZZLYMODULE_H_ */
