#ifndef TILED_BYTES_PRIVATE_HPP
#define TILED_BYTES_PRIVATE_HPP

//------------------------------------------------------------------------------------------------//
//      INCLUDES
//------------------------------------------------------------------------------------------------//

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// -- typeid
#include <cxxabi.h>

// -- rapidxml::
// -- xml_node
#include "../../deps/rapidxml/rapidxml.hpp"
// I try not to mangle up type names for third party APIs. However this class is used so often that
// I can justify it with proper documentation...
typedef rapidxml::xml_node<> XmlNode;

// TiledBytes public API
#include "../include/tiledbytes.hpp"


//----/ INCLUDES /--------------------------------------------------------------------------------//



namespace tb
{



//------------------------------------------------------------------------------------------------//
//      UTILS
//------------------------------------------------------------------------------------------------//

    template<class T> const char* asTypeName()
    {
        const char* type_name = typeid(T).name();

        // type_name not gaurunteed to be human-readable if using gcc/clang compilers so we need to
        // demangle it.
    #if defined(__clang__) || defined(__GNUG__)
        int s;
        const char *demangled = abi::__cxa_demangle(type_name, nullptr, nullptr, &s);
        if(s == 0) {
            type_name = demangled;
        } else {
            printf("Error[%d] demangling type name, using non-human-readable version\n", s);
        }
        if (demangled) {
            std::free(demangled);
        }
    #endif

        return type_name;
    }

    void loadXml(const std::string& fp, std::string &content, rapidxml::xml_document<>* doc);

//----/ UTILS /-----------------------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      XML ATTRIBUTES
//------------------------------------------------------------------------------------------------//
    inline bool stob(const std::string& str)
    {
        if(str == "false" || str == "False") {
            return false;
        } else if (str == "true" || str == "True") {
            return true;
        }
        throw std::invalid_argument(str);
    };

    template <class T> void split(const std::string &s, const char delim, std::vector<T> &result)
    {
        std::istringstream iss(s);
        for (std::string item; std::getline(iss, item, delim);) {
            std::stringstream val(item);
            T v;
            val >> v;
            result.push_back(v);
        }
    };

    template<class T> T attr(const XmlNode *n, const char* key)
    {
        if (!n) {
            throw std::out_of_range(key);
        }

        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        T val;
        if (!n_attr) {
            throw std::out_of_range(key);
        }
        std::istringstream ss(n_attr->value());
        ss >> val;
        return val;
    };

    template<class T> T attr_if(const XmlNode *n, const char* key)
    {
        if (!n) {
            return T();
        }

        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            return T();
        }

        T val;
        std::istringstream ss(n_attr->value());
        ss >> val;
        return val;
    };

    template <> bool attr(const XmlNode *n, const char *key);

    template <> std::string attr(const XmlNode *n, const char* key);

    template <> const std::string attr(const XmlNode *n, const char* key);

    template <> const char* attr(const XmlNode *n, const char* key);

    template <> bool attr_if(const XmlNode *n, const char* key);

    template <> std::string attr_if(const XmlNode *n, const char* key);

    template <> const std::string attr_if(const XmlNode *n, const char* key);

    template <> const char* attr_if(const XmlNode *n, const char* key);

//----/ XML ATTRIBUTES /--------------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      TILED PROJECT LOADING
//------------------------------------------------------------------------------------------------//

    // DECLARED IN PUBLIC HEADER

//----/ TILED PROJECT LOADING /-------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      DATA EXTRACTION
//------------------------------------------------------------------------------------------------//

    template <typename T, typename... Types>
    void extract(const XmlNode* node, T& dest_obj, Types... vars) {
        // to do -- set error flag
        ERRCODE = ERR::CODE::INVALID_EXTRACT_OBJECT;
        printf("Error: Invalid or unknown type being extracted '%s'\n", asTypeName<T>());
    }

    template <typename T, typename... Types>
    T extract(const XmlNode* node, Types... vars) {
        T dest_obj;
        extract<T>(node, dest_obj, vars...);
        return dest_obj;
    }

    template <> void extract(const XmlNode *node, Property& prp);

    template <> void extract(const XmlNode* node, TileRect& rect);

    template <> void extract(const XmlNode* node, PropertyMap& prp_map);

    template <> void extract(const XmlNode* node, Rect& rect);

    template <> void extract(const XmlNode* node, RectMap& rect_map);

    template <> void extract(const XmlNode* node, RectList& rect_list);

    template <> void extract(const XmlNode* node, Image& image);

    template <> void extract(const XmlNode* tile_node, FrameList& frames);

    template <> void extract(const XmlNode* node, Wangset& wang_set);

    template <> void extract(const XmlNode* node, WangsetList& wangset_list);

    template <> void extract(const XmlNode* node, TileList& tile_list);

    template <> void extract(const XmlNode* tileset_node, TilesetMap& tileset_map);

    template <> void extract(const XmlNode* lyr_node, TileLayer& tile_lyr, const int tilewidth, const int tileheight);

    template <> void extract(const XmlNode* lyr_node, ObjectLayer& obj_lyr);

    template <> void extract(const XmlNode* lyr_node, GroupedLayer& grp_lyr, const int width, const int height);

//----/ DATA EXTRACTION /-------------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      WANGSETS
//------------------------------------------------------------------------------------------------//

struct WangsetMeta {
    const std::string& type;
    const int total, offset, comma_skip;
} EdgeSet   {"edge",   4, 0, 4},
  CornerSet {"corner", 4, 1, 4},
  FullSet   {"full",   8, 0, 2};


void asSet(const XmlNode* node, WangtileMap& map, WangsetMeta& setmeta);

void asEdgeSet(const XmlNode* node, WangtileMap& map);

void asCornerSet(const XmlNode* node, WangtileMap& map);

void asFullSet(const XmlNode* node, WangtileMap& map);

//----/ WANGSETS /--------------------------------------------------------------------------------//



} // namespace tb

#endif // TILED_BYTES_PRIVATE_HPP
