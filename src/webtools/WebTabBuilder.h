/*
 * WebTabBuilder.h
 *
 *  Created on: Mar 14, 2014
 *      Author: visio
 */

#ifndef WEBTABBUILDER_H_
#define WEBTABBUILDER_H_

#include <string>
#include <list>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

class WebTabBuilder {
private:

	struct tab_s{
		string tab_name;
		string tab_content;
	};

	list<tab_s> tabs;
	string saved_build;

	string container_name;
	string tab_content_class;
	string tab_name_class;

public:
	WebTabBuilder();
	virtual ~WebTabBuilder();

	void addTab(string name, string content);

	string build(bool save = false){

		if(container_name.empty())
			container_name = "tabs";

		string build_string = "<div id=\"" + container_name +"\"><ul>";

		string build_content;
		list<tab_s>::iterator it = tabs.begin();

		int n = 1;

		for(;it != tabs.end(); it++){
			std::stringstream out; // TODO neefektivne, nahradit vlastnym.
			out << n;
			build_string +=  "<li><a href=\"#tabs-" + out.str() +"\">"+ (*it).tab_name +"</a></li>";
			build_content += "<div id=\"tabs-" + out.str() + "\"><p>" + (*it).tab_content + "</p></div>";
			n++;
		}

		build_string += "</ul>";
		build_string += build_content + "</div>";
		build_string += "<script> $(function() {$( \"#"+ container_name +"\" ).tabs(); });</script>";

		if(save)
			saved_build = build_string;

		return build_string;
	}


	string getPreBuiltString(){
		return saved_build;
	}


};

#endif /* WEBTABBUILDER_H_ */
