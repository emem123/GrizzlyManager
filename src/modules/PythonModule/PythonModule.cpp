/*
 * PythonModule.cpp
 *
 *  Created on: 9.3.2014
 *      Author: vlado
 */

#include "PythonModule.h"

PythonModule::PythonModule()
{
	name = "Python";
	slug = "python";
}

PythonModule::~PythonModule()
{
	// TODO Auto-generated destructor stub
}

std::string PythonModule::onRequest(const map<string,string>* query)
{
	string line;
	//---------------------Loading css and javascripts BEGIN----------------------------------
	std::string response  = "<script src=\"modules/libPythonModule/codemirror.js\"></script>";
				response += "<link rel=\"stylesheet\" href=\"modules/libPythonModule/codemirror.css\">";
				response += "<link rel=\"stylesheet\" type=\"text/css\" href=\"modules/libPythonModule/python_module.css\">";
				response += "<script src=\"modules/libPythonModule/mode/python/python.js\"></script>";
				response += "<script src=\"modules/libPythonModule/placeholder.js\"></script>";
    //---------------------Loading css and javascripts END----------------------------------

				//Following JavaScript replace space character with "/space/" sequence, reason is url encoding
				response += "<script type=\"text/javascript\">$(function() {$('#python_form').submit(function() {";
				response += "var srctext = $('textarea#sourcecode').val(); $('textarea#sourcecode').val(srctext.replace(new RegExp(' ', 'g'),\"/space/\"));";
				response += "return true; }); }); </script>";

				response += "<div class=\"python_input_container\">Source code: <form name=\"python_form\" id=\"python_form\" action=\"\" method=\"get\"><textarea placeholder=\"Put your code here...\" id=\"sourcecode\" name=\"sourcecode\">";

	std::string sourceCode;
	std::string cmdInput;
	std::string pythonOutput = "";
	std::string tempFileName = "temp.py";

	char buffer[128];
	ofstream tempFileOutput;
	FILE* pipe;

	tempFileOutput.open(tempFileName.c_str());

	try
	{
		sourceCode = query->at("sourcecode");
	}
	catch(std::out_of_range){

	}

	//------------------Replacing /space/ sequence back to space character------------
	string search = "/space/";
	string replace = " ";

	for(size_t pos = 0; ;pos += replace.length())
	{
	    pos = sourceCode.find(search, pos);
	    if( pos == string::npos )
	    	break;
	    sourceCode.erase(pos, search.length());
	    sourceCode.insert(pos, replace);
	}

	//put sourcecode to temp file
	tempFileOutput << sourceCode;
	tempFileOutput.close();

	cmdInput = "python " + tempFileName + " 2>&1";

	pipe = popen(cmdInput.c_str(), "r");


	if(!pipe)
		pythonOutput = "Error while output processing!";

	//get output from terminal
	while(!feof(pipe))
	{
		if(fgets(buffer, 128, pipe) != NULL)
		{
			pythonOutput += buffer;
		}
	}

	response += sourceCode + "</textarea><input type=\"submit\" value=\"Run code!\" onclick=\"beforeSubmit();\"/></form></div>";
	response += "<script>var myCodeMirror = CodeMirror.fromTextArea(sourcecode, {lineNumbers:true});</script>";
	response += "<div class=\"python_output_container\">Output: <textarea readonly class=\"python_textarea\" placeholder=\"Output...\" name=\"output\">" + pythonOutput + "</textarea></div>";

	pclose(pipe);

	return response;
}

std::string PythonModule::getModuleDescription()
{
	return "Module for running source code in Python.";
}

void PythonModule::init(){}

extern "C"
{
	void* createInstance()
	{
		return (void*)new PythonModule();
	}
}
