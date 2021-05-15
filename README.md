# Usage

In *one* file before including the xmlout header, define `XMLOUT_IMPLEMENTATION`. This will include the implementation in that file. You may include the file in whatever other segments of your code require it, as long as only one

There are two independent api's available for writing XML files. If you're writing files and don't need to manipulate the file at all before it's written, you can write as you go using the `xml_stream` api. If you want to create the whole document (generally because you want to manipulate it in some way), you can use the `xml_node` api. Example usages for using either follow below.

## Usage : xml_stream


## Usage : xml_node


# Todo
Add comments