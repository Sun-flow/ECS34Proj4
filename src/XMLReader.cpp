#include "XMLReader.h"
#include <iostream>

CXMLReader::CXMLReader(std::istream &is) : DInput(is){
    DParser = XML_ParserCreate(0);

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
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    Entity.DType = SXMLEntity::EType::StartElement;
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    Entity.DNameData = static_cast<const char *>(name); 
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    Entity.SetAttribute(name, atts[0]);
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    std::cout << "Name: " << Entity.DNameData << std::endl;
    Reader->BufferedEntity.push_back(Entity);
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;

}

void CXMLReader::EndElemHandler(void *userData, const XML_Char *name){
    auto Reader = static_cast<CXMLReader *>(userData);
    SXMLEntity Entity;
    Entity.DType = SXMLEntity::EType::EndElement;
    Entity.DNameData = static_cast< const char* >(name); 

}

bool CXMLReader::End(){
    if(!DInput.eof()){
		DInput.peek();
	}
    return DInput.eof();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata){
    char Buffer[1024];
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    DInput.read(Buffer, sizeof(Buffer));
    std::cout << __FILE__<< "@ " << __LINE__ << std::endl;
    XML_Parse(DParser, Buffer, DInput.gcount(), DInput.eof());
    std::cout << __FILE__<< "@ " << __LINE__ << std::endl;

    //std::cout << "Name: " << BufferedEntity.front().DNameData << std::endl;
    //entity = BufferedEntity.front();
    std::cout << __FILE__<< "@ " << __LINE__ << std::endl;
    //BufferedEntity.pop_front();
    std::cout << __FILE__<< "@ " << __LINE__ << std::endl;
    return true;
}