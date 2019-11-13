#include <vector>
#include <iostream>
#include "CSVReader.h"


CCSVReader::CCSVReader(std::istream &in):DIn(in) {
	csv_init(&DParser, CSV_STRICT);//pass a pointer to the struct object, initialized parser

}

CCSVReader::~CCSVReader(){
	csv_fini(&DParser, EndOfColumn, EndOfRow, NULL);
	csv_free(&DParser);

}
        
bool CCSVReader::End() const{
	if(!DIn.eof()){
		DIn.peek();
	}
	return DIn.eof() and DBufferedRows.empty();
}

void CCSVReader::EndOfColumn(void *str, size_t len, void *reader){
	auto Reader = static_cast<CCSVReader *>(reader);
	auto Column = std::string(static_cast<const char *>(str), len);
	Reader->DCurrentRow.push_back(Column);
	std::cout << "@ " << __LINE__ << " Column = \"" << Column << "\"" << std::endl;
}

void CCSVReader::EndOfRow(int ch, void *reader){
	auto Reader = static_cast<CCSVReader *>(reader);
	Reader->DBufferedRows.push_back(Reader->DCurrentRow);
	Reader->DCurrentRow.clear();
	std::cout << "Row @ " << __LINE__ << std::endl;

}

bool CCSVReader::ReadRow(std::vector< std::string > &row){
	while(DBufferedRows.empty() and not End()){

		char Buffer[1024];
		DIn.read(Buffer, sizeof(Buffer));
		csv_parse(&DParser, Buffer, DIn.gcount(), EndOfColumn, EndOfRow, this);
		if(DIn.eof()){
			csv_fini(&DParser, EndOfColumn, EndOfRow, this);
			break;
		}
	}
	if(DBufferedRows.empty()){
		return false;
	}
	
	row = DBufferedRows.front();
	DBufferedRows.pop_front();
	return true;
}