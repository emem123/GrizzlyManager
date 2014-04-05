/*
 * WebTabBuilder.cpp
 *
 *  Created on: Mar 14, 2014
 *      Author: visio
 */

#include "WebTabBuilder.h"

WebTabBuilder::WebTabBuilder() {
	// TODO Auto-generated constructor stub

}

WebTabBuilder::~WebTabBuilder() {
	// TODO Auto-generated destructor stub
}

void WebTabBuilder::addTab(string name, string content){
	tab_s tab;
	tab.tab_name = name;
	tab.tab_content = content;
	tabs.push_back(tab);
}

