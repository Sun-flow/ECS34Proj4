#include "CSVReader.h"
#include "CSVWriter.h"
#include "XMLReader.h"
#include "XMLWriter.h"
#include "XMLEntity.h"
#include <iostream>
#include <map>
#include <iterator>

int main(){

    std::cout << "MAIN IS HERE" << std::endl;

    
        
    CXMLReader XMLReader(inputXML); //Get manifest, needs update on file input

    struct Gender{
        int male = 0;
        int female = 0;
    }

    std::map<std::string , std::map< std::map< std::string , std::map< int , Gender > Names;
    

    while(!XMLReader.end()){//Read in XML data
        
        SXMLEntity entity;
        XMLReader.ReadEntity(entity); //Take in first entity

        //Set up necessary stuff using attributes read in
        std::string inCountry = entity.AttributeValue("Country");
        std::string inYear = entity.AttributeValue("Year");
        CCSVReader CSVReader(entity.AttributeValue("FILENAME"));

        std::vector<std::string> row;

        while(!CSVReader.end()){

            CSVReader.ReadRow(&row); 

            std::string inName = row[0];
            std::string inGender = row[1]
            int inData = row[2];
            if(inGender == "M"){
                Names[inName][inCountry][inYear].male += inData;
            }
            else if(inData == "F"){
                Names[inName].second[inCountry].second[inYear].female += inData;
            }
        }
    }
    
    //Do math about it

    //Use input stream to have user give name, search and return math
}

    

