#include "CSVWriter.h"


CCSVWriter::CCSVWriter(std::ostream &ou){
    outStream = ou;
}

CCSVWriter::~CCSVWriter(){
    fclose(outStream);
}

bool CCSVWriter::WriteRow(const std::vector< std::string > &row){
    for(int i = 0; i < row.size(); i++){
        outStream.write(row, row.size());
    }
}