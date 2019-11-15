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

   
    //Make sure to test wonky quotes (improperly closed, double quotes, etc)

	
}

TEST(CSVReader, MultiLineTest){
     std::stringstream Input("a, b    , cd, e  \x0a, f\x0d,g,h\x0a\x0d");

    CCSVReader Reader(Input);

    std::vector<std::string> Row;

    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(), 4);
    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(), 2);
    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(), 3);
    EXPECT_FALSE(Reader.ReadRow(Row));
    if(5 <= Row.size()){

    }

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

    std::filebuf Out;
    Out.open("Out.txt", std::ios::out);
    
    std::ostream Output(&Out);


    CCSVWriter Writer(Output);

    EXPECT_TRUE(Writer.WriteRow(Row));
    /*EXPECT_EQ(Row.size(), 5);
    if(5 <= Row.size()){
        EXPECT_EQ(Row[0],"1");
        EXPECT_EQ(Row[1],"2");
        EXPECT_EQ(Row[2],"3");
        EXPECT_EQ(Row[3],"4");
        EXPECT_EQ(Row[4],"5");
    }

    EXPECT_TRUE(Reader.End());*/

    Out.close();
}

TEST(CSVWriter, MultiLineTest){

}

