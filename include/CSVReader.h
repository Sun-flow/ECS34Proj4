#ifndef CSVREADER_H 	  			 	 
#define CSVREADER_H

#include <istream>
#include <string>
#include <vector>
#include <list>
#include <csv.h>

class CCSVReader{

	bool end;
    protected:

		std::list < std::vector < std::string > > Buffered;
		std::vector< std::string > curRow;
		std::istream &In;
		struct csv_parser Data; //i need to initialize or parser will be lost
		static void CallBack(void* data, size_t type, void* callData);
		static void CallBack2(int c, void* data);

    public:
        CCSVReader(std::istream &in);
        ~CCSVReader();
        
        bool End() const;
        bool ReadRow(std::vector< std::string > &row);
};

#endif
