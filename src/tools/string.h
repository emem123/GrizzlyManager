/*
 * string.h
 *
 *  Created on: Mar 18, 2014
 *      Author: visio
 */

#ifndef STRING_H_
#define STRING_H_

#include <string>

using namespace std;

char toStringIntbuffer[12];
char toStringDoubleBuffer[22];

const char* toString(const int &input){
	string s;
	int t;
	if(input < 0)
		t = -input;
	else
		t = input;

	int i = 11;
	toStringIntbuffer[10] = 0;

	do{
		toStringIntbuffer[i] =  t%10 + '0';
		--i;
		t/=10;
	}while(t > 0);

	if(input < 0)
		toStringIntbuffer[i] = '-';
	else
		toStringIntbuffer[i] = ' ';

	return &toStringIntbuffer[i];
}

const char* toStringHex(const int &input){
	string s;
	int t;
	int h;
	if(input < 0)
		t = -input;
	else
		t = input;

	int i = 9;
	toStringIntbuffer[10] = 0;

	do{
		h = t%16;
		if(h > 9)
			toStringIntbuffer[i] =  t%16 + '7';
		else
			toStringIntbuffer[i] =  t%16 + '0';

		--i;
		t/=16;

	}while(t > 0);


	toStringIntbuffer[i] = 'x';
	--i;
	toStringIntbuffer[i] = '0';
	--i;

	if(input < 0)
		toStringIntbuffer[i] = '-';
	else
		toStringIntbuffer[i] = ' ';

	return &toStringIntbuffer[i];
}


#endif /* STRING_H_ */
