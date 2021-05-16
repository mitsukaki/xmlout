#pragma once

#include <vector>
#include <string>
#include <stack>
#include <map>

#ifndef XMLOUT_H
#define XMLOUT_H

namespace xmlout
{
    // private functions
    namespace
    {
        void write_tag(
            void (*writer)(std::string),
            const std::string &tag,
            std::map<std::string, std::string> &attributes,
            bool is_empty);
    }

    /* DEFINITIONS */
    class xml_node
    {
    private:
        std::vector<xml_node*> m_children;

        std::map<std::string, std::string> m_attributes;

        std::string m_tag;

    public:
        xml_node(std::string tag) : m_tag{tag} {};

        xml_node* insert_start(xml_node* xml_node_to_add);
        xml_node* insert_end(xml_node* xml_node_to_add);
        xml_node* insert(xml_node* xml_node_to_add, int index);

        xml_node* set(std::string& attribute, std::string& value);
        xml_node* set_all(std::map<std::string, std::string>& m_attributes);

        void write(void (*writer)(std::string));
    };

    class xml_stream
    {
    private:
        void (*m_writer)(std::string);

        std::stack<std::string> m_tag_stack;

    public:
        xml_stream(void (*writer)(std::string)) {
            m_writer = writer;
        };

        xml_stream* write_open(const std::string& m_tag);
        xml_stream* write_open(
            const std::string& m_tag,
            std::map<std::string, std::string>& m_attributes
        );

        xml_stream* write_close();

        xml_stream* write_empty(const std::string& m_tag);
        xml_stream* write_empty(
            const std::string& m_tag,
            std::map<std::string, std::string>& m_attributes
        );

        xml_stream* write_comment(const std::string& comment);
    };

    /* IMPLEMENTATION */
    #ifdef XMLOUT_IMPLEMENTATION

    // private functions
    namespace
    {
        void write_tag(
            void (*writer)(std::string),
            const std::string &tag,
            std::map<std::string, std::string> &attributes,
            bool is_empty)
        {
            writer("<");
            writer(tag);

            std::map<std::string, std::string>::iterator it;
            for (it = attributes.begin(); it != attributes.end(); it++)
            {
                writer(" ");
                writer(it->first);
                writer("=\"");
                writer(it->second);
                writer("\"");
            }

            if (is_empty) writer("/>");
            else writer(">");
        }
    }

    xml_node* xml_node::insert_start(xml_node* xml_node_to_add)
    {
        m_children.insert(m_children.begin(), xml_node_to_add);
        return this;
    }

    xml_node* xml_node::insert_end(xml_node* xml_node_to_add)
    {
        m_children.push_back(xml_node_to_add);
        return this;
    }
    
    xml_node* xml_node::insert(xml_node* xml_node_to_add, int index)
    {
        m_children.insert(m_children.begin() + index, xml_node_to_add);
        return this;
    }

    xml_node* xml_node::set(std::string& attribute, std::string& value)
    {
        m_attributes[attribute] = value;
        return this;
    }

    xml_node* xml_node::set_all(std::map<std::string, std::string>& attributes)
    {
        std::map<std::string, std::string>::iterator it;
        for (it = attributes.begin(); it != attributes.end(); it++)
            m_attributes.insert(std::pair<std::string, std::string>(
                it->first, it->second));

        return this;
    }

    void xml_node::write(void (*writer)(std::string))
    {
        // write tag
        write_tag(writer, m_tag, m_attributes, false);

        // write children
        std::vector<xml_node*>::iterator it;
        for (it = m_children.begin(); it != m_children.end(); ++it)
            (*it)->write(writer);

        // close tag
        writer("</");
        writer(m_tag);
        writer(">");
    }

    xml_stream* xml_stream::write_open(
        const std::string& tag)
    {
        // write tag
        m_tag_stack.push(tag);
        m_writer("<");
        m_writer(tag);
        m_writer(">");
        
        return this;
    }

    xml_stream* xml_stream::write_open(
        const std::string& tag, std::map<std::string, std::string>& attributes)
    {
        // write tag
        m_tag_stack.push(tag);
        write_tag(m_writer, tag, attributes, false);
        return this;
    }

    xml_stream* xml_stream::write_close()
    {
        // write closing tag
        m_writer("</");
        m_writer(m_tag_stack.top());
        m_writer(">");

        m_tag_stack.pop();

        return this;
    }

    xml_stream* xml_stream::write_empty(const std::string& tag)
    {
        // write tag
        m_writer("</");
        m_writer(m_tag_stack.top());
        m_writer(">");

        m_tag_stack.pop();
        return this;
    }

    xml_stream* xml_stream::write_empty(
        const std::string& tag, std::map<std::string, std::string>& attributes)
    {
        write_tag(m_writer, tag, attributes, true);
        return this;
    }

    xml_stream* xml_stream::write_comment(const std::string& comment)
    {
        m_writer("<!-- ");
        m_writer(comment);
        m_writer(" -->");

        return this;
    }

    #endif // XMLOUT_IMPLEMENTATION
}

#endif // XMLOUT_H