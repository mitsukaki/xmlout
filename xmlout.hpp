#include <vector>
#include <string>
#include <stack>
#include <map>

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

    // ** DEFINITIONS **
    class xml_node
    {
    private:
        std::vector<xml_node*> m_xml_nodes;

        std::map<std::string, std::string> m_attributes;

        std::string m_tag;

    public:
        xml_node(std::string tag) : m_tag{tag} {}

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

        std::stack m_tag_stack;

    public:
        xml_stream(T stream) : m_out_stream{stream};

        xml_stream* write_open(
            const std::string &m_tag,
            std::map<std::string, std::string>& m_attributes
        );

        xml_stream* write_close();
        xml_stream* write_empty(
            const std::string &m_tag,
            std::map<std::string, std::string>& m_attributes
        );

        xml_stream* write_comment();
    };

    // ** IMPLEMENTATION **
    #ifdef XMLOUT_IMPLEMENTATION

    // private functions
    namespace
    {
        template <typename T>
        void write_tag(
            const T &out_stream,
            const std::string& tag,
            std::map<std::string, std::string> &attributes,
            bool is_empty)
        {
            m_out_stream << "<" << m_tag;
            for (it = attribtues.begin(); it != attribtues.end(); it++)
                m_out_stream << " \"" << it->first << "\"=\"" << it->second << "\"";

            if (is_empty) m_out_stream << ">";
            else m_out_stream << "/>";
        }
    }

    xml_node* xml_node::insert_start(xml_node* xml_node_to_add)
    {
        xml_node.insert(m_xml_nodes.begin(), xml_node_to_add);
        return this;
    }

    xml_node* xml_node::insert_end(xml_node* xml_node_to_add)
    {
        m_xml_nodes.push_back(xml_node);
        return this;
    }
    
    xml_node* xml_node::insert(xml_node* xml_node_to_add, int index)
    {
        xml_node.insert(m_xml_nodes.begin() + index, xml_node_to_add);
        return this;
    }

    xml_node* xml_node::set(std::string& attribute, std::string& value)
    {
        m_attributes[attribute] = value;
    }

    xml_node* xml_node::set_all(std::map<std::string, std::string>& attributes)
    {
        std::map<std::string, std::string>::iterator it;
        for (it = attributes.begin(); it != attributes.end(); it++)
            m_attributes.insert(it->first, it->second);
    }

    template <typename T>
    void xml_node::write(const T &m_out_stream)
    {
        // write m_tag
        write_tag(m_out_stream, m_tag, m_attributes, false);

        // write children
        std::vector<T>::iterator it;
        for (it = m_xml_nodes.begin(); it != m_xml_nodes.end(); ++it)
            it->write(m_out_stream);

        // close m_tag
        m_out_stream << "</" << m_tag << ">";
    }

    xml_stream* xml_stream::write_open(
        const std::string& m_tag, std::map<std::string, std::string>& m_attributes)
    {
        // write m_tag
        write_tag(m_out_stream, m_tag, m_attributes, false);
        return this;
    }

    xml_stream* xml_stream::write_close()
    {
        m_out_stream << "</" << m_tag_stack.pop() << ">";
        return this;
    }

    xml_stream* xml_stream::write_inline(
        const std::string& m_tag, std::map& attribtues)
    {
        write_tag(m_out_stream, m_tag, m_attributes, true)
        return this;
    }

    #endif // XMLOUT_IMPLEMENTATION
}
