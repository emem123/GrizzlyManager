/*
 * GrizzlyHandler.h
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#ifndef GRIZZLYHANDLER_H_
#define GRIZZLYHANDLER_H_

#include "mongoose/MGHandler.h"

class GrizzlyHandler : public MGHandler{
public:
	GrizzlyHandler();
	virtual ~GrizzlyHandler();

	int onError(mg_connection* conn);
	int onChange(mg_connection * conn);
	int onRequest(mg_connection * conn);


};

#endif /* GRIZZLYHANDLER_H_ */
