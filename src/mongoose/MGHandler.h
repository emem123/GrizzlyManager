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

#ifndef MGHANDLER_H_
#define MGHANDLER_H_

#include "mongoose.h"

class MGHandler {
public:
	MGHandler();
	virtual ~MGHandler();

	virtual int onError(mg_connection* conn) = 0;
	virtual int onChange(mg_connection * conn) = 0;
	virtual int onRequest(mg_connection * conn) = 0;
};

#endif /* MGHANDLER_H_ */
