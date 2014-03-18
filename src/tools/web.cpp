/*
 * web.cpp
 *
 *  Created on: 14.3.2014
 *      Author: vlado
 */

#include "web.h"

string decodeURL(string &param)
{
    string ret;
    char character;
    unsigned int i;
    int correctChar;

    for (i = 0;i < param.length();i++)
    {
        if(int(param[i]) == 37)
        {
            sscanf(param.substr(i+1,2).c_str(), "%x", &correctChar);
            character = static_cast<char>(correctChar);
            i = i + 2;
            ret += character;
        }
        else if(param[i] == '+'){
        	ret += ' ';
        }
        else
        {
            ret += param[i];
        }
    }
    return ret;
}
