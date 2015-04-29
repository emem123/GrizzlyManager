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

#ifndef SYSTEMINFO_H_
#define SYSTEMINFO_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

#include "../../GrizzlyModule.h"
#include "../../webtools/WebTabBuilder.h"

class SystemInfo : public GrizzlyModule{

public:
	SystemInfo();
	~SystemInfo();
	std::string getModuleDescription(){return "Module writes system informations and paints graph of CPU usage.";}
	std::string onRequest(const map<string,string>* query);
	void init();

};

#endif /* SYSTEMINFO_H_ */
