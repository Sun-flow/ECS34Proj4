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

	//should have more tests
}

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
	//EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);
    //EXPECT_FALSE(Entity.DNameData == "uuuu");
	//Find new way to test

	EXPECT_TRUE(Reader.ReadEntity(Entity, true));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(Entity.DNameData, "other");
	EXPECT_TRUE(Reader.ReadEntity(Entity, true));
	EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(Entity.DNameData, "tag");

	//should have more tests
}

TEST(XMLWriter, EmptyTest){

    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    std::filebuf Out;
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    std::ostream Output(&Out);
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    
    CXMLWriter Writer(Output);
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;

    SXMLEntity entity;
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;

    EXPECT_FALSE(Writer.WriteEntity(entity));
    std::cout << __FILE__ << "@: " << __LINE__ << std::endl;
    std::cout << "End Empty Test" << std::endl;
	
}

TEST(XMLWriter, SimpleTest){
    std::stringstream Input("<tag><other></other></tag>");
    CXMLReader Reader(Input);

    std::filebuf Out;
    Out.open("XMLOutSimpleTest.txt", std::ios::out);

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

    /*EXPECT_EQ(Output, "<tag><other></other></tag>");*/
}

