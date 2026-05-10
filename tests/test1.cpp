#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "../include/print.hpp"

TEST(PrintTest, FileOutput) {
    std::string text = "Hello, World!";
    std::string filename = "test.txt";
    
    // Записываем текст в файл
    print(text, filename);
    
    // Читаем весь файл целиком
    std::ifstream in(filename);
    std::string result;
    std::getline(in, result);  // Используем getline вместо operator>>
    
    EXPECT_EQ(result, text);
}

TEST(PrintTest, StreamOutput) {
    std::string text = "Hello, World!";
    std::stringstream ss;
    
    // Выводим в строковый поток
    print(text, ss);
    
    EXPECT_EQ(ss.str(), text);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
