#ifndef CORE_INC_HPP
#define CORE_INC_HPP

// C++ STL
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

// Xml parser lib
#include "../rapidxml/rapidxml.hpp"
namespace rx = rapidxml;

// C STL -- easily gets type name from a class T
#include <cxxabi.h>
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

// TiledBytes public API objects/typedefs/functions
#include "../include/tiledbytes.hpp"


#endif // COMMON_INC