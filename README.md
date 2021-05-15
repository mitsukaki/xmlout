# Usage

In *one* file before including the xmlout header, define `XMLOUT_IMPLEMENTATION`. This will include the implementation in that file. You may include the file in whatever other segments of your code require it, as long as only one

There are two independent api's available for writing XML files. If you're writing files and don't need to manipulate the file at all before it's written, you can write as you go using the `xml_stream` api. If you want to create the whole document (generally because you want to manipulate it in some way), you can use the `xml_node` api. Example usages for using either follow below.

## Usage : xml_stream

```cpp
// this function is called whenever the xml_stream wants to write out
void write_func(std::string text)
{
    // print the text to the console
    std::cout << text;
}

int main()
{
    // create an xml stream and pass the writing function
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

    /*
        Every function returns a pointer to the object
        so that methods can be chained.
    */
}
```

The complete, compileable example is in the examples folder.

## Usage : xml_node


# Todo
- add proper documentation
- support lambda's for writer functions
- support comments in the xml_node flow
- check if actually XML compliant in any way lmao