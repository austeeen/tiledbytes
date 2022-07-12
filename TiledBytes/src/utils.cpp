#include "utils.hpp"

namespace tb
{

void loadXml(const char *fp, std::string &content, rx::xml_document<>* doc)
{
    std::ifstream file(fp);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    content = buffer.str();
    doc->parse<0>(&content[0]);
}

bool stob(const std::string& str)
{
    if(str == "false" || str == "False") {
        return false;
    } else if (str == "true" || str == "True") {
        return true;
    }
    throw std::invalid_argument(str);
}

template <> bool attr(const rx::xml_node<> *n, const char *key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    return stob(std::string(n_attr->value()));
}

template <> const char* attr(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    return n_attr->value();
}

template <> bool attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        return false;
    }
    return stob(std::string(n_attr->value()));
}

template <> const char* attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        return nullptr;
    }
    return n_attr->value();
}


} // namespace tb
