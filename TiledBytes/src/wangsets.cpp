#include "wangsets.hpp"

void asSet(rx::xml_node<>* node, WangtileMap& map, WangsetMeta& setmeta)
{
    for (rx::xml_node<> *wtile = node->first_node("wangtile"); wtile; wtile = wtile->next_sibling("wangtile"))
    {
        const char* wang_id_str = attr<const char*>(wtile, "wangid");
        int wang_id = 0;
        for (int i = setmeta.offset; i < setmeta.total; i ++) {
            // to do:
            // making a very magical assumption here: '1' == alpha, '2' == texture
            // do more work/research/testing with the Tiled wangsets and variations and come back
            // to this to support all varieties.
            if (wang_id_str[i * setmeta.comma_skip] == '2') {
                wang_id |= 1 << i;
            }
        }

        map.insert(std::pair<const int, const Wangtile>(
            attr<int>(wtile, "tileid"),
            Wangtile {
                attr<int>(wtile, "tileid"),
                wang_id,
                wang_id_str
            })
        );
    }
}

const Wangset newWangset(rx::xml_node<>* node)
{
    std::string type = std::string(attr<const char*>(node, "type"));

    WangtileMap map;
    if (type == "edge") {
        asEdgeSet(node, map);
    } else if (type == "corner") {
        asEdgeSet(node, map);
    } else if (type == "full") {
        asEdgeSet(node, map);
    } else {
        printf("Warning: wangset type unknown: %s", type.c_str());
    }

    return Wangset {
        attr_if<const char*>(node, "name"),
        type.c_str(),
        map
    };
}