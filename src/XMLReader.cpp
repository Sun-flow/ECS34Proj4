#include "XMLReader.h"
#include <iostream>

CXMLReader::CXMLReader(std::istream &is) : DInput(is){
    DParser = XML_ParserCreate(NULL);
    XML_SetUserData(DParser, this);
    //set handlers/callback functions (Chardata, startelement, endelement)
    XML_SetElementHandler(DParser, StartElemHandler, EndElemHandler);
    XML_SetCharacterDataHandler(DParser, CharDataHandler);
}

CXMLReader::~CXMLReader(){
    XML_ParserFree(DParser);
}

void CXMLReader::CharDataHandler(void *userData, const XML_Char *s, int len){
	SXMLEntity Entity;
    auto Reader = static_cast<CXMLReader *>(userData);
	Entity.DType = SXMLEntity::EType::CharData;
	Entity.DNameData =	std::string(s, len);
	Reader->BufferedEntity.push_back(Entity);

}

void CXMLReader::StartElemHandler(void *userData, const XML_Char *name, const XML_Char **atts){
    auto Reader = static_cast<CXMLReader *>(userData);
    SXMLEntity Entity;
    Entity.DType = SXMLEntity::EType::StartElement;
    Entity.DNameData = static_cast<const char *>(name); 
    if(atts[0] != NULL){
        for(int i = 0; atts[i] != NULL;i += 2){
            Entity.SetAttribute(std::string(atts[i]), std::string(atts[i+1]));
        }
    }//!!!FIX!!!
    Reader->BufferedEntity.push_back(Entity);
}

void CXMLReader::EndElemHandler(void *userData, const XML_Char *name){
    auto Reader = static_cast<CXMLReader *>(userData);
    SXMLEntity Entity;
    Entity.DType = SXMLEntity::EType::EndElement;
    Entity.DNameData = static_cast< const char* >(name); 

    Reader->BufferedEntity.push_back(Entity);

}

bool CXMLReader::End(){
    if(!DInput.eof()){
		DInput.peek();
	}
    return DInput.eof() and BufferedEntity.empty();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata){
    char Buffer[1024];
    DInput.read(Buffer, sizeof(Buffer));
    XML_Parse(DParser, Buffer, DInput.gcount(), DInput.eof());
	while(BufferedEntity.front().DType == SXMLEntity::EType::CharData && skipcdata) {
        BufferedEntity.pop_front();
	}
    if(!BufferedEntity.empty()){
        entity = BufferedEntity.front();
        BufferedEntity.pop_front();
        return true;
    }
    return false;
}