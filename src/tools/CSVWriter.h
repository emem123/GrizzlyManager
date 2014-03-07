/*
 * CSV.h
 *
 *  Created on: Dec 22, 2013
 *      Author: visio
 */

#ifndef CSV_H_
#define CSV_H_

#include <string>
#include <stdio.h>
#include <fstream>

class CSVWriter {
	FILE* f;
	std::ofstream stream;
	char separator;

public:

	CSVWriter(char* fileName, char sep = ';', bool append = false);

	void writeInt(int data);
	void newLine();
	void writeDouble(double* d);
	void writeString(std::string s);
	void writeFloat(float f);

	~CSVWriter(){
		stream.close();
	}
};

#endif /* CSV_H_ */
