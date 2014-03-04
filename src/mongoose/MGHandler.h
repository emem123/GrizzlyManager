/*
 * MGHandler.h
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
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
