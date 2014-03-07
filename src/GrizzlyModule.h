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
private:
	std::string name;
	std::string slug;

	std::string (*p_module_name)();

public:
	GrizzlyModule();
	virtual ~GrizzlyModule();

	std::string getName(){return name;}
	void setName(const std::string &arg){ name = arg;}
	virtual std::string getModuleName(){ return "kek";}
	virtual std::string getModuleSlug(){ return "slug";}
	virtual std::string getModuleDescription(){ return "kek";}

	std::string onRequest(const char* request);

	virtual void init(){ }
	virtual void resolve(){ }

};

#endif /* GRIZZLYMODULE_H_ */
