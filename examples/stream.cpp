#include <sstream>
#include <iostream>

#define XMLOUT_IMPLEMENTATION
#include "../xmlout.h"

void write_func(std::string text)
{
    std::cout << text;
}

int main()
{
    xmlout::xml_stream xml_output(&write_func);

    // writing an empty node
    std::map<std::string, std::string> attrs = {{"version", "1.0"}};
    xml_output.write_empty("status", attrs);

    // opening a block
    xml_output.write_open("parent");

    // opening another block (child)
    xml_output.write_open("child");

    // close both blocks (applying chaining)
    xml_output.write_close()->write_close();
}