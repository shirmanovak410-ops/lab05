#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "../include/print.hpp"

TEST(PrintTest, OutputToFile) {
    std::string text = "Hello, World!";
    std::string filename = "test_output.txt";
    
    std::ofstream out(filename);
    out << text;
    out.close();
    
    std::ifstream in(filename);
    std::string result;
    in >> result;
    
    EXPECT_EQ(result, text);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
