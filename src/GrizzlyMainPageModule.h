/*
 * GrizzlyMainPageModule.h
 *
 *  Created on: Mar 8, 2014
 *      Author: visio
 */

#ifndef GRIZZLYMAINPAGEMODULE_H_
#define GRIZZLYMAINPAGEMODULE_H_
#include "GrizzlyModule.h"
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
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

	std::string onRequest(const map<string, string>* query){

		std::map<std::string, GrizzlyModule*>::iterator it;
		std::string res;


		for(it = modules->begin(); it != modules->end(); it++){
			res += "<div class=\"info\">";
			res += "<h3>";
			res += (*it).second->getModuleName();
			res += "</h3><span>";
			res += (*it).second->getModuleDescription();
			res += "</span></div>";
		}

		return res;
	}

};

#endif /* GRIZZLYMAINPAGEMODULE_H_ */
