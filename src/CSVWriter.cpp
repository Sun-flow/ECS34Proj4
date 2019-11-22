#include <string>
#include "CSVWriter.h"
#include "StringUtils.h"
#include <iostream>

CCSVWriter::CCSVWriter(std::ostream &ou):outStream(ou){

}

CCSVWriter::~CCSVWriter(){

}

bool CCSVWriter::WriteRow(const std::vector< std::string > &row){

	std::string editStr;
	for (size_t i = 0; i < row.size(); i++) {
		if (i != row.size() - 1)
			editStr = editStr + "\"" + row[i] + "\",";
		else
			editStr = editStr + "\"" + row[i] + "\"";
	}
	outStream << editStr << std::endl;
    return true;
}