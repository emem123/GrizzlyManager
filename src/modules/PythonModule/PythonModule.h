/*
 * PythonModule.h
 *
 *  Created on: 9.3.2014
 *      Author: vlado
 */

#ifndef PYTHONMODULE_H_
#define PYTHONMODULE_H_

#include "../../GrizzlyModule.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>

using namespace std;


class PythonModule : public GrizzlyModule
{
public:
	PythonModule();
	virtual ~PythonModule();
	std::string onRequest(const map<string,string>* query);
	std::string getModuleDescription();
	void init();
};


#endif /* PYTHONMODULE_H_ */
