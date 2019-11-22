#include <gtest/gtest.h>
#include "CSVReader.h"
#include "CSVWriter.h"
#include <sstream>
#include <iostream>
#include <fstream>

TEST(CSVReader, EmptyTest){
    std::stringstream Input;

    CCSVReader Reader(Input);

    EXPECT_TRUE(Reader.End());
}

TEST(CSVReader, SingleLineTest){
    std::stringstream Input(" 1,2 ,  3       ,4,5\x0d\x0a");

    CCSVReader Reader(Input);

    std::vector<std::string> Row;

    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(), 5);
    if(5 <= Row.size()){
        EXPECT_EQ(Row[0],"1");
        EXPECT_EQ(Row[1],"2");
        EXPECT_EQ(Row[2],"3");
        EXPECT_EQ(Row[3],"4");
        EXPECT_EQ(Row[4],"5");
    }

    EXPECT_TRUE(Reader.End());
}

TEST(CSVReader, MultiLineTest){
     std::stringstream Input("a, b    , cd, e  \x0a, f\x0d,g,h\x0a\x0d");

    CCSVReader Reader(Input);

    std::vector<std::string> Row;

    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(), 4);
    if(4 <= Row.size()){
        EXPECT_EQ(Row[0],"a");
        EXPECT_EQ(Row[1],"b");
        EXPECT_EQ(Row[2],"cd");
        EXPECT_EQ(Row[3],"e");
    }
    
    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(), 2);
    if(4 <= Row.size()){
        EXPECT_EQ(Row[0],"");
        EXPECT_EQ(Row[1],"f");
    }

    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(), 3);
    if(4 <= Row.size()){
        EXPECT_EQ(Row[0],"");
        EXPECT_EQ(Row[1],"g");
        EXPECT_EQ(Row[2],"h");
    }

    EXPECT_FALSE(Reader.ReadRow(Row));

    EXPECT_TRUE(Reader.End());
}

TEST(CSVWriter, EmptyTest){
    std::stringstream Output;

    CCSVWriter Writer(Output);

    std::vector<std::string> Row;
    EXPECT_TRUE(Writer.WriteRow(Row));
}

TEST(CSVWriter, SingleLineTest){

    std::stringstream Input(" 1,2 ,  3       ,4,5\x0d\x0a");
    CCSVReader Reader(Input);
    std::vector<std::string> Row;

    EXPECT_TRUE(Reader.ReadRow(Row));

	std::ofstream Out("testbin/SimpleLineWriter.csv");
	CCSVWriter Writer(Out);

    EXPECT_TRUE(Writer.WriteRow(Row));

    std::ifstream Input2("testbin/SimpleLineWriter.csv");
	CCSVReader Reader2(Input2);

    std::vector<std::string> Row2;
    EXPECT_TRUE(Reader2.ReadRow(Row2));


    EXPECT_EQ(Row2.size(), 5);

    if(5 <= Row.size()){
        EXPECT_EQ(Row[0],"1");
        EXPECT_EQ(Row[1],"2");
        EXPECT_EQ(Row[2],"3");
        EXPECT_EQ(Row[3],"4");
        EXPECT_EQ(Row[4],"5");
    }

    EXPECT_TRUE(Reader.End());
}

TEST(CSVWriter, MultiLineTest){

    std::stringstream Input("a, b    , cd, e  \x0a, f\x0d,g,h\x0a\x0d");
    CCSVReader Reader(Input);
    std::vector<std::string> Row;

    std::ofstream Out("testbin/MultiLineWriter.csv");
	CCSVWriter Writer(Out);

    while(!Reader.End()){
        EXPECT_TRUE(Reader.ReadRow(Row));
        EXPECT_TRUE(Writer.WriteRow(Row));
    }

    std::ifstream Input2("testbin/MultiLineWriter.csv");
	CCSVReader Reader2(Input2);

    std::vector<std::string> Row2;

    EXPECT_TRUE(Reader2.ReadRow(Row2));
    EXPECT_EQ(Row2.size(), 4);
    if(4 <= Row2.size()){
        EXPECT_EQ(Row2[0],"a");
        EXPECT_EQ(Row2[1],"b");
        EXPECT_EQ(Row2[2],"cd");
        EXPECT_EQ(Row2[3],"e");
    }
    
    EXPECT_TRUE(Reader2.ReadRow(Row2));
    EXPECT_EQ(Row2.size(), 2);
    if(4 <= Row2.size()){
        EXPECT_EQ(Row2[0],"");
        EXPECT_EQ(Row2[1],"f");
    }

    EXPECT_TRUE(Reader2.ReadRow(Row2));
    EXPECT_EQ(Row2.size(), 3);
    if(4 <= Row2.size()){
        EXPECT_EQ(Row2[0],"");
        EXPECT_EQ(Row2[1],"g");
        EXPECT_EQ(Row2[2],"h");
    }

    EXPECT_TRUE(Reader2.End());
}

