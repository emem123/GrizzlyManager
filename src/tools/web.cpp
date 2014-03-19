/*
C++ server for web-driven administration with module support.
Copyright (C) 2014 Vladimír Bartošík, Martin Kuzma, Marek Moravčík

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
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
        if(param[i] == '%')
        {
            sscanf(param.substr(i+1,2).c_str(), "%x", &correctChar);
            character = static_cast<char>(correctChar);
            i = i + 2;
            ret += character;
        }
        else
        {
            ret += param[i];
        }
    }
    return ret;
}
