#ifndef TB_UTIL_HPP
#define TB_UTIL_HPP

#include "common.hpp"

void loadXml(const char *fp, std::string &content, rx::xml_document<>* doc);

template <class T>
void split(const std::string &s, char delim, std::vector<T> &result);

bool stob(const std::string& str);

inline const float min(float a, float b) { return (a < b) ? a : b; };
inline const float max(float a, float b) { return (a < b) ? b : a; };

template<class T> T attr(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    T val;
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    std::istringstream ss(n_attr->value());
    ss >> val;
    return val;
};

template<class T> T attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    T val;
    if (n_attr == nullptr) {
        return val;
    }
    std::istringstream ss(n_attr->value());
    ss >> val;
    return val;
};

template <> bool attr(const rx::xml_node<> *n, const char *key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    return stob(std::string(n_attr->value()));
};
template <> const char* attr(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        throw std::out_of_range(key);
    }
    return n_attr->value();
};
template <> bool attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        return false;
    }
    return stob(std::string(n_attr->value()));
};
template <> const char* attr_if(const rx::xml_node<> *n, const char* key)
{
    rx::xml_attribute<> *n_attr = n->first_attribute(key);
    if (n_attr == nullptr) {
        return nullptr;
    }
    return n_attr->value();
};

#endif // TB_UTIL_HPP
