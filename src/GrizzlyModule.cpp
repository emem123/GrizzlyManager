/*
 * GrizzlyModule.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: visio
 */

#include "GrizzlyModule.h"

GrizzlyModule::GrizzlyModule() {
}

GrizzlyModule::~GrizzlyModule() {
	// TODO Dealokacia vsetkeho.
}

std::string GrizzlyModule::onRequest(const map<string,string>* query){
	std::string response = "<form> First name: <input type=\"text\" name=\"firstname\" value=\"";
	std::string firstname;
	std::string lastname;
	try{
		firstname = query->at("firstname");
		lastname = query->at("lastname");
	}catch(std::out_of_range){

	}

	response += firstname;
	response += "\"> <br> Last name: <input type=\"text\" name=\"lastname\" value=\"";
	response += lastname;
	response +=	"\"> <input type=\"submit\" value=\"Submit\"></form> ";

	if(firstname.size() != 0){
		response += "Your name is ";
		response += firstname;
		response += ".";
	}


	return response;
}
