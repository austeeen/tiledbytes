#include "tmx.hpp"

void loadTmx(const char *filepath, Tmx& usr_tmx)
{
    rx::xml_document<>* doc = new rx::xml_document<>();
    std::string content = "";
    loadXml(filepath, content, doc);
    if (doc == nullptr || content == "") {
        printf("Error loading tmx file: %s\n", filepath);
        return;
    }

    rx::xml_node<> *map = doc->first_node();
    usr_tmx.width = attr<int>(map, "width");
    usr_tmx.height = attr<int>(map, "height");
    usr_tmx.tilewidth = attr<int>(map, "tilewidth");
    usr_tmx.tileheight = attr<int>(map, "tileheight");

    rx::xml_node<> *node = map->first_node();
    while(node != nullptr) {
        std::string type = std::string(node->name());
        if (type == "tileset") {
            usr_tmx.tilesets.insert(std::pair<int, const Tileset>(
                attr<int>(node, "firstgid"),
                newTileset(node))
            );
        } else if (type == "layer") {
            usr_tmx.layers.push_back(newTileLayer(node));
        } else if (type == "objectgroup") {
            usr_tmx.layers.push_back(newTileLayer(node));
        } else if (type == "group") {
            usr_tmx.layers.push_back(newGroupedLayer(node));
        } else {
            printf("Warning: unknown layer type: %s\n", type.c_str());
        }
        node = node->next_sibling();
    }
    delete doc;
}

const Image _newImageSource(rx::xml_node<>* node, const char* node_name)
{
    rx::xml_node<> *img_node = node->first_node("image");
    if (!img_node) {
        printf("Warning: tileset %s has no image source\n", node_name);
        return Image{};
    }
    return Image {
        attr<const char*>(img_node, "source"),
        attr<int>(img_node, "width"),
        attr<int>(img_node, "width")
    };
}

const Tileset newTileset(rx::xml_node<>* node)
{
    // Get basic attributes about this tileset -- to be used to generate this Tilesets' member data
    // by the subroutines herein
    const char* name = attr<const char*>(node, "name");
    const int tilecount = attr<int>(node, "tilecount");
    const int columns = attr<int>(node, "columns");
    const int tilewidth =attr<int>(node, "tilewidth");
    const int tileheight = attr<int>(node, "tileheight");


    // Create the image source
    const Image image = _newImageSource(node, name);


    // Create a map of entries in the tileset so we can look up information about the tile later on.
    std::map<const int, rx::xml_node<>*> tileset_entries;
    for (rx::xml_node<> *tnode = node->first_node("tile"); tnode; tnode = tnode->next_sibling()) {
        if (std::string(tnode->name()) == "tile") {
            tileset_entries.insert(
                std::pair< const int, rx::xml_node<>* >(attr<int>(tnode, "id"), tnode)
            );
        }
    }


    // Iterate through all tiles in this tileset and create a tile entry;
    Tilelist tiles;
    for (int i = 0; i < tilecount; i ++)
    {
        // Use the tile's position in the tileset (i) + columns in this tileset + tile dimensions to
        // find this tile's texture rectangle
        const TextureRect t_rect {
            i,
            // x, y, width, height
            i % columns, i / columns, tilewidth, tileheight
        };
        // a tileset has no positional data, but we can include the tile's size for as a curtesy
        const PositionRect p_rect {
            0, 0,
            tilewidth, tileheight
        };

        // If the tile is in our tileset entry map, then include any information in the map entry.
        if (tileset_entries.count(i) != 0) {
            rx::xml_node<> *tile_entry = tileset_entries.at(i);
            tiles.push_back(Tile {
                i,
                p_rect,
                t_rect,
                attr_if<const char*>(tile_entry, "type"),
                extract<RectList>(tile_entry),
                extract<PropertyMap>(tile_entry)
            });
        } else {
            // If no entry exists for this tile id, just create a tile with an id and texture rect
            tiles.push_back(Tile {
                i,
                p_rect,
                t_rect
            });
        }
    }


    // Collect any wang sets
    WangsetList wangset_list;
    rx::xml_node<> *ws = node->first_node("wangsets");
    if (ws) {
        for (rx::xml_node<> *wn = ws->first_node("wangset"); wn; wn = wn->next_sibling("wangset")) {
            wangset_list.push_back(newWangset(wn));
        }
    }

    // Finally, return a Tileset from all of the data we've collected for this tile set entry
    return Tileset {
        attr<int>(node, "firstgid"),
        tilewidth,
        tileheight,
        tilecount,
        columns,
        name,
        image,
        tiles,
        wangset_list,
        extract<PropertyMap>(node)
    };
}
const TileLayer newTileLayer(rx::xml_node<>* node)
{
    // todo
}
const ObjectLayer newObjectLayer(rx::xml_node<>* node)
{
    // todo
}
const GroupedLayer newGroupedLayer(rx::xml_node<>* node)
{
    std::vector<const Layer> sublayers;
    rx::xml_node<> *sub_layer = node->first_node();
    while(sub_layer) {
        std::string type = std::string(sub_layer->name());
        if (type == "layer") {
            sublayers.push_back(newTileLayer(node));
        } else if (type == "objectgroup") {
            sublayers.push_back(newObjectLayer(node));
        } else if (type == "group") {
            sublayers.push_back(newGroupedLayer(node));
        } else {
            printf("Warning: unknown layer type: %s\n", type.c_str());
        }
        node = node->next_sibling();
    }
    return GroupedLayer(
            attr<int>(node, "id"),
            attr_if<const char*>(node, "name"),
            sublayers
        );
}
