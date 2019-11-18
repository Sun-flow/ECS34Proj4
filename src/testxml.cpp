#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "XMLEntity.h"
#include <sstream>
#include <iostream>
#include <fstream>

TEST(XMLReader, EmptyTest){
    std::stringstream Input;

    CXMLReader Reader(Input);

    EXPECT_TRUE(Reader.End());
	
}

TEST(XMLReader, SimpleTest){
    std::stringstream Input("<tag><other></other></tag>");
    CXMLReader Reader(Input);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "tag");
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "other");
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "other");
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "tag");

    //should have more tests
}

TEST(XMLReader, SimpleCharacterDataTest) {
	std::stringstream Input("<tag><other>uuuu</other></tag>");
	CXMLReader Reader(Input);
	SXMLEntity Entity;

	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(Entity.DNameData, "tag");
	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(Entity.DNameData, "other");

	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);
	EXPECT_EQ(Entity.DNameData, "uuuu");

	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(Entity.DNameData, "other");
	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(Entity.DNameData, "tag");


    std::ifstream Input2("proj4data/smallmanifest.xml");
	CXMLReader Reader2(Input2);
	SXMLEntity inEntity;

	EXPECT_TRUE(Reader2.ReadEntity(inEntity));
	EXPECT_EQ(inEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(inEntity.DNameData, "NAMEFILES");
    EXPECT_TRUE(Reader2.ReadEntity(inEntity, true));
	EXPECT_EQ(inEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(inEntity.DNameData, "NAMEFILE");
    EXPECT_TRUE(inEntity.AttributeExists("FILENAME"));
    EXPECT_EQ(inEntity.AttributeValue("FILENAME"), "ENG1996.csv");
    EXPECT_TRUE(inEntity.AttributeExists("COUNTRY"));
    EXPECT_EQ(inEntity.AttributeValue("COUNTRY"), "ENGLAND");
    EXPECT_TRUE(inEntity.AttributeExists("FILENAME"));
    EXPECT_EQ(inEntity.AttributeValue("YEAR"), "1996");

    EXPECT_TRUE(Reader2.ReadEntity(inEntity, true));
    EXPECT

    EXPECT_TRUE(Reader2.ReadEntity(inEntity, true));
	EXPECT_EQ(inEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(inEntity.DNameData, "NAMEFILE");
    EXPECT_TRUE(inEntity.AttributeExists("FILENAME"));
    EXPECT_EQ(inEntity.AttributeValue("FILENAME"), "ENG1997.csv");
    EXPECT_TRUE(inEntity.AttributeExists("COUNTRY"));
    EXPECT_EQ(inEntity.AttributeValue("COUNTRY"), "ENGLAND");
    EXPECT_TRUE(inEntity.AttributeExists("FILENAME"));
    EXPECT_EQ(inEntity.AttributeValue("YEAR"), "1997");


    EXPECT_TRUE(Reader2.ReadEntity(inEntity, true));
	EXPECT_EQ(inEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(inEntity.DNameData, "NAMEFILE");
    EXPECT_TRUE(inEntity.AttributeExists("FILENAME"));
    EXPECT_EQ(inEntity.AttributeValue("FILENAME"), "ENG1998.csv");
    EXPECT_TRUE(inEntity.AttributeExists("COUNTRY"));
    EXPECT_EQ(inEntity.AttributeValue("COUNTRY"), "ENGLAND");
    EXPECT_TRUE(inEntity.AttributeExists("FILENAME"));
    EXPECT_EQ(inEntity.AttributeValue("YEAR"), "1998");

	//should have more tests
}

/*TEST(XMLReader, AttributeTest){
    std::stringstream Input("<tag FILENAME=\"ENG1997.csv\"><other>uuuu</other></tag>");
	CXMLReader Reader(Input);
	SXMLEntity Entity;

	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(Entity.DNameData, "tag");
    EXPECT_EQ(Entity.DAttributes[0].first, "FILENAME");
    EXPECT_EQ(Entity.DAttributes[0].second, "ENG1997.csv");
	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(Entity.DNameData, "other");

	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);
	EXPECT_EQ(Entity.DNameData, "uuuu");

	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(Entity.DNameData, "other");
	EXPECT_TRUE(Reader.ReadEntity(Entity));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(Entity.DNameData, "tag");


}
*/

TEST(XMLReader, AvoidingCharacterDataTest) {
	std::stringstream Input("<tag><other>uuuu</other></tag>");
	CXMLReader Reader(Input);
	SXMLEntity Entity;

	EXPECT_TRUE(Reader.ReadEntity(Entity, true));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(Entity.DNameData, "tag");
	EXPECT_TRUE(Reader.ReadEntity(Entity, true));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(Entity.DNameData, "other");

	EXPECT_TRUE(Reader.ReadEntity(Entity, true));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(Entity.DNameData, "other");
	EXPECT_TRUE(Reader.ReadEntity(Entity, true));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(Entity.DNameData, "tag");

	//should have more tests
}

TEST(XMLWriter, EmptyTest){

    std::filebuf Out;
    std::ostream Output(&Out);
    
    CXMLWriter Writer(Output);

    SXMLEntity entity;

    EXPECT_FALSE(Writer.WriteEntity(entity));	
}

TEST(XMLWriter, SimpleTest){
    std::stringstream Input("<tag><other></other></tag>");
    CXMLReader Reader(Input);

    std::filebuf Out;
    Out.open("XMLOutSimpleTest.xml", std::ios::out);

    std::ostream Output(&Out);
    CXMLWriter Writer(Output);

    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_TRUE(Writer.WriteEntity(Entity));
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_TRUE(Writer.WriteEntity(Entity));
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_TRUE(Writer.WriteEntity(Entity));
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_TRUE(Writer.WriteEntity(Entity));

/*
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    std::ifstream inFile("XMLOutSimpleTest.xml");
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    CXMLReader Reader2(inFile);
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    SXMLEntity inEntity;
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;

    EXPECT_TRUE(Reader2.ReadEntity(inEntity));
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    EXPECT_EQ(inEntity.DType, SXMLEntity::EType::StartElement);
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    EXPECT_EQ(inEntity.DNameData, "tag");
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    EXPECT_TRUE(Reader2.ReadEntity(inEntity));
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    EXPECT_EQ(inEntity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(inEntity.DNameData, "other");
    EXPECT_TRUE(Reader2.ReadEntity(inEntity));
    EXPECT_EQ(inEntity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(inEntity.DNameData, "other");
    EXPECT_TRUE(Reader2.ReadEntity(inEntity));
    EXPECT_EQ(inEntity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(inEntity.DNameData, "tag");

    /*EXPECT_EQ(Output, "<tag><other></other></tag>");*/
}

