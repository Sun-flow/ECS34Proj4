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

    

    std::map<std::string , std::map> Names;
    

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
            
            if(!Names.find(inName)){ //If name does not already exist, set up its associated maps. Might be some scoping issues here, but logic stands once those are fixed
                std::map<std::string , int> Values;
                std::map<std::string, int> Gender;
                std::map<std::string, int> Country;
                std::map<std::string, int> Year;
                std::string inGender = row[1]; 
                
                Gender[inGender] = row[2];
                Country[inCountry] = row[2];
                Year[inYear] = row[2];

                Values["Gender"] = Gender;
                Values["Country"] = Country;
                Values["Year"] = Year;
            }
            else{ //In case name already exists, just add new datas. This probably needs some updating to pass right value in to right place.
                Names[inName].second["Gender"][row[1]] += row[2]; //Find inName, add count to its respective map. Structure should be Names< inName , inType< name , value > >
                Names[inName].second["Country"][inCountry] += row[2];
                Names[inName].second["Year"][inYear] += row[2];
            }
        }
    }
    
    //Do math about it

    //Use input stream to have user give name, search and return math
}

    

