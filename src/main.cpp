#include "CSVReader.h"
#include "CSVWriter.h"
#include "XMLReader.h"
#include "XMLWriter.h"
#include "XMLEntity.h"
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
    int Avg;
};

void printData(std::string name, std::string likelySex, double sexProb, int highYear){
    std::cout << "Name: " << name << std::endl;
    std::cout << "Likely Sex: " << likelySex << " (" << sexProb << "%)" << std::endl;
    std::cout << "Year: " << highYear << std::endl;
}

int main(){

    std::cout << "MAIN IS HERE" << std::endl;

    std::ifstream Input("proj4data/smallmanifest.xml", std::ifstream::in);
    CXMLReader XMLReader(Input); //Get manifest, needs update on file input

    std::map<std::string , std::map< std::string , std::map< int , Gender > > > Names;
    

    while(!XMLReader.End()){//Read in XML data
        
        SXMLEntity entity;
        XMLReader.ReadEntity(entity); //Take in first entity

        //Set up necessary stuff using attributes read in
        std::string inCountry = entity.AttributeValue("Country");
        std::string inYear = entity.AttributeValue("Year");

        std::ifstream Input(entity.AttributeValue("FILENAME"), std::ifstream::in);
        CCSVReader CSVReader(Input);

        std::vector< std::string > row;

        while(!CSVReader.End()){

            CSVReader.ReadRow(row); 

            std::string inName = row[0];
            std::string inGender = row[1];
            int inData = std::stoi(row[2]);
            if(inGender == "M"){
                Names[inName][inCountry][std::stoi(inYear)].male += inData;
            }
            else if(inGender == "F"){
                Names[inName][inCountry][std::stoi(inYear)].female += inData;
            }
        }
    }
/*
    bool end = false;
    do{
        std::string inName;
        std::cout << "Enter Name>>";
        std::cin >> inName;

        auto countryIter = Names.find(inName)->second.begin();
        double sexProb;
        std::string likelySex;
        RollingAvg likelyYear;

        RollingAvg avg;
        
        
        while(!countryIter.end()){ //Increment country
            
            int males = 0;
            int females = 0;
            auto yearIter = countryIter->second.begin();
            while(!yearIter.end()){
                males += yearIter.male;
                females += yearIter.female;
                
                avg.totals[avg.index%3] = males + females;
                avg.index++;
                double tempAvg = 0;
                for(int i = 0; i < 3; i++){
                    tempAvg += avg.total[i]; 
                }
                if(tempAvg >= avg.Avg){
                    avg.Avg = tempAvg;
                    avg.MidYear = yearIter.first - 1;
                }
                likelyYear = avg.MidYear;

                yearIter++;
            }

            if(males > females){
                likelySex = "M";
                sexProb = males/(males + females);
            }
            else if(females > males){
                likelySex = "F";
                sexProb = females/(males + females);

            }
            else{
                likelySex = "M/F";
                sexProb = 50
            }

            countryIter++;
        }
        printData(inName, likelySex, sexProb, likelyYear)
    }while(!end);
    //Do math about it*/

    //Use input stream to have user give name, search and return math
}

    
