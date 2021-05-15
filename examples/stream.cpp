#include <sstream>
#include <iostream>

#define XMLOUT_IMPLEMENTATION
#include "../xmlout.h"

int main()
{
    std::stringstream ss;
    xmlout::xml_stream<std::stringstream> xml_output(ss);

    // writing an empty node
    xml_output.write_empty("status", {{"version", "1.0"}});

    // opening a block
    xml_output.write_open("parent");

    // opening another block (child)
    xml_output.write_open("child");

    

    // closing a block
    xml_output.write_close();
}