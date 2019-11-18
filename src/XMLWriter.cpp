#include "XMLWriter.h"
#include <iostream>

CXMLWriter::CXMLWriter(std::ostream &os):outStream(os){

}

CXMLWriter::~CXMLWriter(){

}
        
bool CXMLWriter::Flush(){
    while(!EndElements.empty()){
        WriteEntity(EndElements.back());
        EndElements.pop_back();
    }
    if(EndElements.empty()){
        return true;
    }
    else{
        return false;
    }
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity){
    if(entity.DType == SXMLEntity::EType::StartElement){
        if(entity.DNameData == ""){
            return false;
        }
        SXMLEntity endElem;
        endElem.DType = SXMLEntity::EType::EndElement;
        endElem.DNameData = entity.DNameData;
        EndElements.push_back(endElem);
        outStream << "<" << entity.DNameData << ">";
        return true;
    }
    else if(entity.DType == SXMLEntity::EType::EndElement){
        if(entity.DNameData == EndElements.back().DNameData){
            EndElements.pop_back();
        }
        outStream << "</" << EndElements.back().DNameData << ">";
        return true;
    }
    else if(entity.DType == SXMLEntity::EType::CharData){
        outStream << entity.DNameData;
        return true;
    }
    else{
        return false;
    }
}