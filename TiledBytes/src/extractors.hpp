#ifndef TB_EXTRACTORS_HPP
#define TB_EXTRACTORS_HPP

#include "common.hpp"
#include "tiled_core.hpp"

template <class T> void extract(const rx::xml_node<>* node, T& container) {
    printf("Error: Invalid type '%s' used to get rects from object group\n", asTypeName<T>());
};

template <class T> const T extract(const rx::xml_node<>* node) {
    T container;
    extract<T>(node, container);
    return container;
}

inline Property _newProperty(const rx::xml_node<> *n)
{
    return Property {
        attr_if<const char*>(n, "name"),
        attr_if<const char*>(n, "type"),
        attr_if<const char*>(n, "value")
    };
}

inline Rect _newRect(const rx::xml_node<> *n)
{
    return Rect {
        attr_if<int>(n, "id"),
        attr_if<int>(n, "gid"),
        attr_if<int>(n, "x"),
        attr_if<int>(n, "y"),
        attr_if<int>(n, "width"),
        attr_if<int>(n, "height"),
        attr_if<const char*>(n, "name"),
        attr_if<const char*>(n, "type"),
        extract<PropertyMap>(n)
    };
}

template <> void extract(const rx::xml_node<>* node, PropertyMap& container) {
    rx::xml_node<> *n = node->first_node("property");
    while(n != nullptr) {
        container.insert(std::pair<const char*, const Property>(
            attr<const char*>(n, "name"),
            _newProperty(n)
        ));
        n = n->next_sibling();
    }
};

template <> void extract(const rx::xml_node<>* node, RectMap& container) {
    rx::xml_node<> *og = node->first_node("objectgroup");
    if (og) {
        rx::xml_node<> *obj = og->first_node("object");
        while(obj != nullptr) {
            container.insert(std::pair<const int, Rect>(attr<int>(node, "id"), _newRect(obj)));
            obj = obj->next_sibling();
        }
    }
};

template <> void extract(const rx::xml_node<>* node, RectList& container) {
    rx::xml_node<> *og = node->first_node("objectgroup");
    if (og) {
        rx::xml_node<> *obj = og->first_node("object");
        while(obj != nullptr) {
            container.push_back(_newRect(obj));
            obj = obj->next_sibling();
        }
    }
};


#endif // TB_EXTRACTORS_HPP
