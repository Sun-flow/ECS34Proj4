#ifndef XMLWRITER_H 	  			 	 
#define XMLWRITER_H

#include "XMLEntity.h"
#include <stack>
#include <istream>
#include <ostream>

class CXMLWriter{
    private:
        std::ostream &outStream;

        std::vector< SXMLEntity > OpenElements;
        std::vector< SXMLEntity > EndElements;

    public:
        CXMLWriter(std::ostream &os);
        ~CXMLWriter();
        
        bool Flush();
        bool WriteEntity(const SXMLEntity &entity);
};

#endif
                                      