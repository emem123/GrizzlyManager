/*
 * GrizzlyModule.h
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#ifndef GRIZZLYMODULE_H_
#define GRIZZLYMODULE_H_

#include <dlfcn.h>
#include <string>

class GrizzlyModule {
public:
	GrizzlyModule();
	virtual ~GrizzlyModule();

	virtual std::string getModuleName() = 0;
	virtual std::string getModuleSlug() = 0;

	virtual void init() = 0;
	virtual void resolve() = 0;

};

#endif /* GRIZZLYMODULE_H_ */
