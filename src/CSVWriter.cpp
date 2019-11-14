#include "CSVWriter.h"
#include <iostream>

CCSVWriter::CCSVWriter(std::ostream &ou):outStream(ou){

}

CCSVWriter::~CCSVWriter(){

}
//Take in vector of strings and put quotes around all of the entries ini a copy vector
bool CCSVWriter::WriteRow(const std::vector< std::string > &row){
    for(auto str : row){
        outStream << str << ", ";
    }
    std::cout << std::endl;
    return true;
}

//Carriage return new line is a single line