# Usage

In *one* file, define `XMLOUT_IMPLEMENTATION` to include the implementation, and subsequently include the header wherever you need it.

There are two independent api's available for writing XML files. If you're writing files and don't need to manipulate the file at all before it's written, you can write as you go using the `xml_stream` api. If you want to create the whole document (generally because you want to manipulate it in some way), you can use the `xml_node` api. Example usages for using either follow below.

## Usage : xml_stream


## Usage : xml_node


# Todo
Add comments