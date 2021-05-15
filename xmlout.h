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
        template <typename T>
        void write_tag(
            const T& out_stream,
            const std::string& tag,
            std::map<std::string, std::string>& attributes,
            bool is_empty
        );
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

        template <typename T>
        void write(const T& m_out_stream);
    };

    template <typename T>
    class xml_stream
    {
    private:
        T m_out_stream;

        std::stack<std::string> m_tag_stack;

    public:
        xml_stream(T stream) : m_out_stream{stream} {};

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

        // TODO: xml_stream* write_comment();
    };

    /* IMPLEMENTATION */
    #ifdef XMLOUT_IMPLEMENTATION

    // private functions
    namespace
    {
        template <typename T>
        void write_tag(
            const T& out_stream,
            const std::string& tag,
            std::map<std::string, std::string>& attributes,
            bool is_empty)
        {
            out_stream << "<" << tag;
            std::map<std::string, std::string>::iterator it;
            for (it = attributes.begin(); it != attributes.end(); it++)
                out_stream << " \"" << it->first << "\"=\"" << it->second << "\"";

            if (is_empty) out_stream << "/>";
            else out_stream << ">";
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
            m_attributes.insert(it->first, it->second);

        return this;
    }

    template <typename T>
    void xml_node::write(const T& m_out_stream)
    {
        // write tag
        write_tag(m_out_stream, m_tag, m_attributes, false);

        // write children
        std::vector<xml_node*>::iterator it;
        for (it = m_children.begin(); it != m_children.end(); ++it)
            (*it)->write(m_out_stream);

        // close tag
        m_out_stream << "</" << m_tag << ">";
    }

    template <class T>
    xml_stream<T>* xml_stream<T>::write_open(
        const std::string& tag)
    {
        // write tag
        m_tag_stack.push(tag);
        m_out_stream << "<" << tag << ">";
        return this;
    }

    template <class T>
    xml_stream<T>* xml_stream<T>::write_open(
        const std::string& tag, std::map<std::string, std::string>& attributes)
    {
        // write tag
        m_tag_stack.push(tag);
        write_tag(m_out_stream, tag, attributes, false);
        return this;
    }

    template <class T>
    xml_stream<T>* xml_stream<T>::write_close()
    {
        m_out_stream << "</" << m_tag_stack.pop() << ">";
        return this;
    }

    template <class T>
    xml_stream<T>* xml_stream<T>::write_empty(const std::string& tag)
    {
        // write tag
        m_out_stream << "<" << tag << "/>";
        return this;
    }

    template <class T>
    xml_stream<T>* xml_stream<T>::write_empty(
        const std::string &tag, std::map<std::string, std::string>& attributes)
    {
        write_tag(m_out_stream, tag, attributes, true);
        return this;
    }

#endif // XMLOUT_IMPLEMENTATION
}

#endif // XMLOUT_H