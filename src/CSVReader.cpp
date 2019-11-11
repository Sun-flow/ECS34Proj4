#include <vector>
#include <iostream>
#include "CSVReader.h"


CCSVReader::CCSVReader(std::istream &in):In(in) {

	//starting with CSV_STRICT
	end = true; //initializes end to false 
	csv_init(&Data, CSV_STRICT);//pass a pointer to the struct object, initialized parser

}

CCSVReader::~CCSVReader(){

	csv_fini(&Data, CallBack, CallBack2, NULL);
	csv_free(&Data);

}
        
bool CCSVReader::End() const{
	return end;
}

void CCSVReader::CallBack(void* data, size_t type, void* callData) {//void CCSVReader::CallBack(const char* data, size_t type, void* callData) {

	//callback for column in a row
	//std::cout << __LINE__ << " inside callback1 " << __FILE__ << std::endl;

	CCSVReader* ptr = static_cast<CCSVReader*>(callData);
	const char* dataPtr = static_cast<const char*>(data);
	std::string dataString(dataPtr, type); //converting the c-string into a C++ string
	ptr->curRow.push_back(dataString); //shouldn't be nullterminated
	//std::cout << "the currect size of the Row vector is: " << ptr->curRow.size() << std::endl;
	//std::cout << "the string pushed in is: " << dataString << std::endl;

}

void CCSVReader::CallBack2(int c, void* callData) {
	//callback for end of row
	//std::cout << __LINE__ << " inside callback2 "<< __FILE__ << std::endl;

	CCSVReader* ptr = static_cast<CCSVReader*>(callData);
	ptr->Buffered.push_back(ptr->curRow);
	ptr->curRow.clear();

}

bool CCSVReader::ReadRow(std::vector< std::string > &row){
	//std::cout << __LINE__ << " inside readRow " << __FILE__ << std::endl;
	while (Buffered.empty()) {
	//	std::cout << __LINE__ << " inside readRow " << __FILE__ << " checking if Buffered is empty()\n";

		char TempData[128];
		In.read(TempData, sizeof(TempData)); 
		size_t BytesRead = In.gcount(); 
		csv_parse(&Data, TempData, BytesRead, CallBack, CallBack2, this); 
		if (!(Buffered.empty())) {

			row = Buffered.front(); //get first element
			//std::cout << "current vector of strings\n";
			//for (auto str : row)
			//	std::cout << str << " ";
			//std::cout << std::endl;
			Buffered.pop_front(); //delete first element
			//std::cout << __LINE__ << " inside " << __FILE__ << std::endl;

			return true;
		}
	}
	//std::cout << __LINE__ << " inside " << __FILE__ << std::endl;

	return false;
}
