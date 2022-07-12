#ifndef TB_UTIL_HPP
#define TB_UTIL_HPP

#include "core.hpp"

namespace tb
{
void loadXml(const char *fp, std::string &content, rx::xml_document<>* doc);

template <class T>
void split(const std::string &s, const char delim, std::vector<T> &result)
{
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim);) {
        std::stringstream val(item);
        T v;
        val >> v;
        result.push_back(v);
    }
}
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

template <> bool attr(const rx::xml_node<> *n, const char *key);
template <> const char* attr(const rx::xml_node<> *n, const char* key);

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

template <> bool attr_if(const rx::xml_node<> *n, const char* key);
template <> const char* attr_if(const rx::xml_node<> *n, const char* key);

} // namespace tb

#endif // TB_UTIL_HPP
