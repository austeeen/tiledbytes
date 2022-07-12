#include "tsx.hpp"

namespace tb
{

void loadTsx(const char *filepath, Tsx& usr_tsx)
{
    rx::xml_document<>* doc = new rx::xml_document<>();
    std::string content = "";
    loadXml(filepath, content, doc);
    if (doc == nullptr || content == "") {
        printf("Error loading tmx file: %s\n", filepath);
        ERRCODE = ERR::CODE::FILE_LOAD_ERROR;
        return;
    }

    XmlNode *tsx = doc->first_node();

    getTileList(tsx, usr_tsx);
    extract<PropertyMap>(tsx, usr_tsx.properties);
    newImageSource(tsx, usr_tsx.image);

    delete doc;
}

void newImageSource(XmlNode* node, Image& image)
{
    XmlNode *img_node = node->first_node("image");
    if (!img_node) {
        printf("Warning: tileset has no image source\n");
        return;
    }
    image.source = attr<const char*>(img_node, "source");
    image.width = attr<int>(img_node, "width");
    image.height = attr<int>(img_node, "height");
}

void getTileList(XmlNode* node, Tsx& usr_tsx)
{
    usr_tsx.name = attr<const char*>(node, "name");
    usr_tsx.tilewidth = attr<int>(node, "tilewidth");
    usr_tsx.tileheight = attr<int>(node, "tileheight");
    usr_tsx.tilecount = attr<int>(node, "tilecount");
    usr_tsx.columns = attr<int>(node, "columns");

    // Create a map of entries in the tileset so we can look up information about the tile later on.
    std::map<const int, XmlNode*> tileset_entries;
    for (XmlNode *tnode = node->first_node("tile"); tnode; tnode = tnode->next_sibling()) {
        if (std::string(tnode->name()) == "tile") {
            tileset_entries.insert(
                std::pair< const int, XmlNode* >(attr<int>(tnode, "id"), tnode)
            );
        }
    }

    // Iterate through all tiles in this tileset and create a tile entry;
    for (int i = 0; i < usr_tsx.tilecount; i ++)
    {
        // Use the tile's position in the tileset (i) + columns in this tileset + tile dimensions to
        // find this tile's texture rectangle
        const TextureRect t_rect {
            i,
            // x, y, width, height
            i % usr_tsx.columns, i / usr_tsx.columns, usr_tsx.tilewidth, usr_tsx.tileheight
        };
        // a tileset has no positional data, but we can include the tile's size for as a curtesy
        const PositionRect p_rect {
            0, 0,
            usr_tsx.tilewidth, usr_tsx.tileheight
        };

        // If the tile is in our tileset entry map, then include any information in the map entry.
        if (tileset_entries.count(i) != 0) {
            XmlNode *tile_entry = tileset_entries.at(i);
            usr_tsx.tiles.push_back(Tile {
                i,
                p_rect,
                t_rect,
                attr_if<const char*>(tile_entry, "type"),
                extract<RectList>(tile_entry),
                extract<PropertyMap>(tile_entry)
            });

            XmlNode *animation = tile_entry->first_node("animation");

            // if there's an animation entry, then create a new entry
            if (animation) {
                newAnimation(animation, usr_tsx, i);
            }

        } else {
            // If no entry exists for this tile id, just create a tile with an id and texture rect
            usr_tsx.tiles.push_back(Tile {
                i,
                p_rect,
                t_rect
            });
        }
    }
}

void newAnimation(XmlNode* node, Tsx& usr_tsx, const int id)
{
    FrameList frames;
    rx::xml_node<> *frame_entry = node->first_node("frame");
    while(frame_entry) {
        frames.push_back({
            attr<int>(frame_entry, "tileid"),
            attr<int>(frame_entry, "duration")
        });
        frame_entry = frame_entry->next_sibling();
    }
    usr_tsx.animations.insert(std::pair<const int, const FrameList>(id, frames));
}

} // namespace tb
