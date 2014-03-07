/*
 * CSV.cpp
 *
 *  Created on: Dec 22, 2013
 *      Author: visio
 */

#include "CSVWriter.h"

CSVWriter::CSVWriter(char* fileName, char sep, bool append){
	//	f = fopen(fileName.c_str(),"rw");
	if(append)
		stream.open(fileName, std::fstream::app);
	else
		stream.open(fileName);

	separator = sep;
}

void CSVWriter::writeInt(int data){
	stream << data << separator;
}

void CSVWriter::newLine(){
	stream << '\n';
}

void CSVWriter::writeDouble(double* d){
	stream << *d << separator;
}

void CSVWriter::writeString(std::string s){
	stream << s << separator;
}

void CSVWriter::writeFloat(float f){
	stream << f << separator;
}
