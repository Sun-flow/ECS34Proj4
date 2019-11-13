#include "XMLReader.h"

CXMLReader::CXMLReader(std::istream &is) : DInput(is){
    DParser = XML_ParserCreate(NULL);

    //set handlers/callback functions (Chardata, startelement, endelement)
    XML_SetElementHandler(DParser, StartElemHandler, EndElemHandler);
    //XML_SetCharacterDataHandler(DParser, CharDataHandler);
}

CXMLReader::~CXMLReader(){
    XML_ParserFree(DParser);
}

void CXMLReader::CharDataHandler(void *userData, const XML_Char *s, int len){
    auto Data = static_cast<CXMLReader *>(userData);
    std::string(s, len);
}

void CXMLReader::StartElemHandler(void *userData, const XML_Char *name, const XML_Char **atts){
    auto Reader = static_cast<CXMLReader *>(userData);
    SXMLEntity Entity;
    Entity.DType = SXMLEntity::EType::StartElement;
    Entity.DNameData = static_cast<const char *>(name); 
    Entity.DAttributes.push_back(atts);
}

void CXMLReader::EndElemHandler(void *userData, const XML_Char *name){
    auto Reader = static_cast<CXMLReader *>(userData);
    SXMLEntity Entity;
    Entity.DType = SXMLEntity::EType::EndElement;
    Entity.DNameData = static_cast<const char* >(name); 

}

bool CXMLReader::End(){

}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata){
    char Buffer[1024];
    DInput.read(Buffer, sizeof(Buffer));
    XML_Parse(DParser, Buffer, DInput.gcount(), DInput.eof());

    entity = BufferedEntity.front();
    BufferedEntity.pop_front();

}