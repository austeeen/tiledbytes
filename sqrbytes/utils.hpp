#ifndef SQR_UTIL_HPP
#define SQR_UTIL_HPP

#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <memory>
#include <map>

namespace sq
{
    template<class T> inline void destroy(T*& p) {
        delete p; p = nullptr;
    }
    template<class T> inline void destroy(std::shared_ptr<T>& p) {
        p.reset();
    }
    template<class K, class V> inline void destroy(std::map<K, V>& map) {
        for (auto& [k, v] : map) { delete v; }
        map.clear();
    }
    template<class T> inline void destroy(std::vector<T>& vec) {
        for (auto& v : vec) { delete v; }
        vec.clear();
    }

    void split(const std::string &s, char delim, std::vector<float> &result);
    void split(const std::string &s, char delim, std::vector<int> &result);
    void split(const std::string &s, char delim, std::vector<std::string> &result);
    std::vector<float> split4(const std::string &s, char delim);
    std::vector<float> split2(const std::string &s, char delim);

    void loadXML(const char *fp, std::string &content, rx::xml_document<>* doc)
    {
        std::ifstream file(fp);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        content = buffer.str();
        doc->parse<0>(&content[0]);
    }

    void split(const std::string &s, char delim, std::vector<float> &result)
    {
        std::istringstream iss(s);
        for (std::string item; std::getline(iss, item, delim); )
            result.push_back(std::stof(item));
    }
    void split(const std::string &s, char delim, std::vector<int> &result)
    {
        std::istringstream iss(s);
        for (std::string item; std::getline(iss, item, delim); )
            result.push_back(std::stoi(item));
    }
    void split(const std::string &s, char delim, std::vector<std::string> &result)
    {
        std::istringstream iss(s);
        for (std::string item; std::getline(iss, item, delim); )
            result.push_back(item);
    }
    std::vector<float> split4(const std::string &s, char delim)
    {
        std::vector<float> result;
        std::istringstream iss(s);
        for (std::string item; std::getline(iss, item, delim); )
            result.push_back(std::stoi(item));
        return result;
    }
    std::vector<float> split2(const std::string &s, char delim)
    {
        std::vector<float> result;
        std::istringstream iss(s);
        for (std::string item; std::getline(iss, item, delim); )
            result.push_back(std::stoi(item));
        return result;
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
    sf::Vector2f stovf(const std::string& str)
    {
        std::vector<std::string> rs;
        split(str, ',', rs);
        if (rs.size() != 2) {
            std::cout << str << " != 2 int/float values" << std::endl;
            throw std::out_of_range(str);
        }
        return sf::Vector2f(std::stof(rs[0]), std::stof(rs[1]));
    }

    inline const float min(float a, float b) { return (a < b) ? a : b; };
    inline const float max(float a, float b) { return (a < b) ? b : a; };

}

#endif // U_UTIL_H
