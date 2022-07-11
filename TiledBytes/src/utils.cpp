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

template <class T>
void split(const std::string &s, char delim, std::vector<T> &result)
{
    std::istringstream iss(s);
    for (std::string item; std::getline(iss, item, delim);) {
        std::stringstream val(item);
        T v;
        val >> v;
        result.push_back(v);
    }
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

} // namespace tb
