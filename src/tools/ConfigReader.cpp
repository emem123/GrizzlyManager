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

#include "ConfigReader.h"

ConfigReader::ConfigReader() {
	// TODO Auto-generated constructor stub

}

ConfigReader::~ConfigReader() {
	// TODO Auto-generated destructor stub
}

void ConfigReader::run(const std::string &filename, bool print){

	std::ifstream stream;
	std::string line;
	stream.open(filename.c_str(),std::fstream::in);

	while(std::getline(stream,line)){

		int pos = 0;
		int initpos = 0;
		int endpos;

		if(line.size() == 0)
			continue;

		initpos = line.find_first_not_of(" \t", 0);
		pos = line.find_first_of(" \t",initpos);

		if(pos == string::npos) // Separator not found , line has no argument, therefore is not interesting.
			continue;

		string name = line.substr(initpos,pos-initpos);
		pos = line.find_first_not_of(" \t",pos);

		if(pos == string::npos)
			continue;

		endpos = line.find_last_not_of(" \t",line.size()-1);

		string value = line.substr(pos,endpos  +1 - pos);
		items[name] = value;

		if(print)
			printf("%s\t%s\n", name.c_str(), value.c_str());
	}
}
