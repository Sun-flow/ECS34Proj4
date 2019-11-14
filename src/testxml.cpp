#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
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
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    SXMLEntity Entity;

    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    EXPECT_EQ(Entity.DNameData, "tag");
    std::cout << __FILE__ << "@ " << __LINE__ << std::endl;
    /*EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "other");
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "other");
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "tag");*/

    //should have more tests
}

