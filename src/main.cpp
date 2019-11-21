#include "CSVReader.h"
#include "CSVWriter.h"
#include "XMLReader.h"
#include "XMLWriter.h"
#include "XMLEntity.h"
#include <cctype>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <queue>

struct Gender{
    int male = 0;
    int female = 0;
};

struct RollingAvg{
    int totals[3];
    int index = 0;
    int Avg = 0;
};

void printData(std::string name, std::string likelySex, double sexProb, int highYear, std::string country){
    std::cout << "Name: " << name << std::endl;
    std::cout << "Country: " << country << std::endl;
    std::cout << "Likely Sex: " << likelySex << " (" << sexProb << "%)" << std::endl;
    std::cout << "Year: " << highYear << std::endl;
}

int main(int argc, char** argv){

    
	
  //  std::ifstream Input("smallmanifest.xml", std::ifstream::in);
	std::ifstream Input(argv[1]);

	CXMLReader XMLReader(Input); //Get manifest, needs update on file input

    std::map<std::string , std::map< std::string , std::map< int , Gender > > > Names;
    

    while(!XMLReader.End()){//Read in XML data
        SXMLEntity entity;

        
        XMLReader.ReadEntity(entity);
	    while(!entity.AttributeExists("FILENAME") and !XMLReader.End()){
			XMLReader.ReadEntity(entity); //Take in first entity
        }
        
        
        //Set up necessary stuff using attributes read in
	
		
        if(entity.AttributeExists("FILENAME")){
            std::string inCountry = entity.AttributeValue("COUNTRY");
            std::string inYear = entity.AttributeValue("YEAR");


            std::ifstream Input("proj4data/" + entity.AttributeValue("FILENAME"), std::ifstream::in);
            CCSVReader Reader(Input);
            std::vector< std::string > row;
            Reader.ReadRow(row);
            while(!Reader.End()){

                Reader.ReadRow(row);

                std::string inName = row[0];
                std::string inGender = row[1];
                int inData = std::stoi(row[2]);
                if(inGender == "M"){

                    Names[inName][inCountry][std::stoi(inYear)].male += inData;
                    Names[inName]["All"][std::stoi(inYear)].male += inData;
                }
                else if(inGender == "F"){

                    Names[inName][inCountry][std::stoi(inYear)].female += inData;
                    Names[inName]["All"][std::stoi(inYear)].female += inData;
                }
            }
        }
    }

    bool end = false;
    do{
        std::string inName;
        std::cout << "Enter Name>>";
        std::cin >> inName;
		size_t i = 0;
		for (auto &ch : inName) {
			inName[i++] = toupper(ch);
		}
		while (Names.find(inName) == Names.end()) {
			std::cout << "No existing Data for name " << inName << std::endl;
			std::cout << "Enter Name>>";
			std::cin >> inName;
            i = 0;
            for (auto &ch : inName) {
			    inName[i++] = toupper(ch);
		    }
		}
        auto countryIter = Names.find(inName)->second.begin();
        double sexProb;
        std::string likelySex;
        int likelyYear;
        

        while(countryIter != Names.find(inName)->second.end()){ //Increment country
            RollingAvg avg;
            double males = 0;
            double females = 0;
            auto yearIter = countryIter->second.begin();
            while(yearIter != countryIter->second.end()){
                males += yearIter->second.male;
                females += yearIter->second.female;
                
                avg.totals[avg.index%3] = yearIter->second.male + yearIter->second.female;
                avg.index++;
                double tempAvg = 0;
                for(int i = 0; i < 3; i++){
                    tempAvg += avg.totals[i]; 
                }
                tempAvg = tempAvg/3;
                if(tempAvg > avg.Avg){
                    avg.Avg = tempAvg;
                    likelyYear = yearIter->first - 1;
                }
                yearIter++;
            }

            if(males > females){
                likelySex = "M";
                sexProb = males/(males + females) * 100;
            }
            else if(females > males){
                likelySex = "F";
                sexProb = females/(males + females) * 100;

            }
            else{
                likelySex = "M/F";
                sexProb = 50;
            }
            printData(inName, likelySex, sexProb, likelyYear, countryIter->first);
            countryIter++;
        }

        
    }while(!end);
    //Do math about it

    //Use input stream to have user give name, search and return math
}

    

