#include "print.hpp"
#include <fstream>

void print(const std::string& text, std::ostream& out) {
    out << text;
}

void print(const std::string& text, const std::string& filename) {
    std::ofstream out(filename);
    out << text;
    out.close();
}
