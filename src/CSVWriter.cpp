#include "CSVWriter.h"
#include <iostream>

CCSVWriter::CCSVWriter(std::ostream &ou):outStream(ou){

}

CCSVWriter::~CCSVWriter(){

}

bool CCSVWriter::WriteRow(const std::vector< std::string > &row){
    std::cout << "Writer cout-put: ";
    for(auto str : row){
        outStream << str << ", ";
        std::cout << str << ", ";
    }
    std::cout << std::endl;
    return true;
}