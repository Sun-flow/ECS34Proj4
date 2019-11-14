#include <vector>
#include <iostream>
#include "CSVReader.h"


<<<<<<< HEAD
CCSVReader::CCSVReader(std::istream &in):In(in) {

	//starting with CSV_STRICT
	end = true; //initializes end to false 
	csv_init(&Data, CSV_STRICT);//pass a pointer to the struct object, initialized parser
=======
CCSVReader::CCSVReader(std::istream &in):DIn(in) {
	csv_init(&DParser, CSV_STRICT);//pass a pointer to the struct object, initialized parser
>>>>>>> b3f8b38f1beb0538f4e73ada81cc6f428c09ce9c

}

CCSVReader::~CCSVReader(){
	csv_fini(&DParser, EndOfColumn, EndOfRow, NULL);
	csv_free(&DParser);

	csv_fini(&Data, CallBack, CallBack2, NULL);
	csv_free(&Data);

}
        
bool CCSVReader::End() const{
<<<<<<< HEAD
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
=======
	if(!DIn.eof()){
		DIn.peek();
	}
	return DIn.eof() and DBufferedRows.empty();
}
>>>>>>> b3f8b38f1beb0538f4e73ada81cc6f428c09ce9c

void CCSVReader::EndOfColumn(void *str, size_t len, void *reader){
	auto Reader = static_cast<CCSVReader *>(reader);
	auto Column = std::string(static_cast<const char *>(str), len);
	Reader->DCurrentRow.push_back(Column);
	std::cout << "@ " << __LINE__ << " Column = \"" << Column << "\"" << std::endl;
}

<<<<<<< HEAD
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
=======
void CCSVReader::EndOfRow(int ch, void *reader){
	auto Reader = static_cast<CCSVReader *>(reader);
	Reader->DBufferedRows.push_back(Reader->DCurrentRow);
	Reader->DCurrentRow.clear();
	std::cout << "Row @ " << __LINE__ << std::endl;

>>>>>>> b3f8b38f1beb0538f4e73ada81cc6f428c09ce9c
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