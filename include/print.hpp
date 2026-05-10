#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>
#include <ostream>
#include <fstream>
#include <sstream>

void print(const std::string& text, std::ostream& out);
void print(const std::string& text, const std::string& filename);

#endif
