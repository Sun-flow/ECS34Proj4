#include "CSVReader.h"


CCSVReader::CCSVReader(std::istream &in){
    inStream = in;
}

CCSVReader::~CCSVReader(){
    fclose(inStream);
}
        
bool CCSVReader::End() const{
    if(inStream.tellg() == inStream.end){
        return true;
    }
    else{
        return false;
    }
}

bool CCSVReader::ReadRow(std::vector< std::string > &row){
    if(inStream.peek() == -1){
        return false;
    }
    row.push_back(inStream.getline());
    inStream.seekg(row.end().size(), SEEK_CUR);
    return true;
}
