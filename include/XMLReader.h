#ifndef XMLREADER_H 	  			 	 
#define XMLREADER_H

#include "XMLEntity.h"
#include <istream>
#include <expat.h>
#include <list>

class CXMLReader{
    private:
        std::istream &DInput;
        XML_Parser DParser;

        std::list<SXMLEntity> BufferedEntity;
    public:
        CXMLReader(std::istream &is);
        ~CXMLReader();
        
        static void CharDataHandler(void *userData, const XML_Char *s, int len);
        static void StartElemHandler(void *userData, const XML_Char *name, const XML_Char **atts);
        static void EndElemHandler(void *userData, const XML_Char *name);


        bool End();
        bool ReadEntity(SXMLEntity &entity, bool skipcdata = false);
};

#endif
