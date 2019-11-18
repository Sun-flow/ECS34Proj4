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
        std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
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
        std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
        outStream << "</" << EndElements.back().DNameData << ">";
        return true;
    }
    else if(entity.DType == SXMLEntity::EType::CharData){
        std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
        outStream << entity.DNameData;
        return true;
    }
    else{
        return false;
    }
}