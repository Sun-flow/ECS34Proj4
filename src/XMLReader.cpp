#include "XMLReader.h"
#include <iostream>

CXMLReader::CXMLReader(std::istream &is) : DInput(is){
    DParser = XML_ParserCreate(NULL);
    XML_SetUserData(DParser, this);
    //set handlers/callback functions (Chardata, startelement, endelement)
    XML_SetElementHandler(DParser, StartElemHandler, EndElemHandler);
    //XML_SetCharacterDataHandler(DParser, CharDataHandler);
}

CXMLReader::~CXMLReader(){
    XML_ParserFree(DParser);
}

void CXMLReader::CharDataHandler(void *userData, const XML_Char *s, int len){
    auto Reader = static_cast<CXMLReader *>(userData);
    std::string(s, len);
}

void CXMLReader::StartElemHandler(void *userData, const XML_Char *name, const XML_Char **atts){
    auto Reader = static_cast<CXMLReader *>(userData);
    SXMLEntity Entity;
    //std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    Entity.DType = SXMLEntity::EType::StartElement;
    //std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    Entity.DNameData = static_cast<const char *>(name); 
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    if(atts[0] != NULL){
        std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
        //Entity.SetAttribute(atts[0].first()), atts[0].second());
    }
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    //std::cout << "Name: " << Entity.DNameData << std::endl;
    Reader->BufferedEntity.push_back(Entity);
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;

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
    return DInput.eof();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata){
    char Buffer[1024];
    DInput.read(Buffer, sizeof(Buffer));
    XML_Parse(DParser, Buffer, DInput.gcount(), DInput.eof());

    entity = BufferedEntity.front();
    BufferedEntity.pop_front();
    return true;
}