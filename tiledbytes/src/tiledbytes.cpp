#include "tiledbytes_priv.hpp"

namespace tb
{

    uint8_t ERRCODE = ERR::CODE::NONE;

//------------------------------------------------------------------------------------------------//
//      FILE IO
//------------------------------------------------------------------------------------------------//

    void loadXml(const std::string& fp, std::string &content, rapidxml::xml_document<>* doc)
    {
        std::ifstream file(fp);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        content = buffer.str();
        doc->parse<0>(&content[0]);
    }

//----/ FILE IO /---------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------------------//
//      XML ATTRIBUTES
//------------------------------------------------------------------------------------------------//

    template <> bool attr(const XmlNode *n, const char *key)
    {
        if (!n) {
            throw std::out_of_range(key);
        }

        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            throw std::out_of_range(key);
        }
        return stob(std::string(n_attr->value()));
    };

    template <> std::string attr(const XmlNode *n, const char* key)
    {
        if (!n) {
            throw std::out_of_range(key);
        }

        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            throw std::out_of_range(key);
        }
        return std::string(n_attr->value());
    }

    template <> const std::string attr(const XmlNode *n, const char* key)
    {
        if (!n) {
            throw std::out_of_range(key);
        }

        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            throw std::out_of_range(key);
        }
        return std::string(n_attr->value());
    }

    template <> const char* attr(const XmlNode *n, const char* key)
    {
        if (!n) {
            throw std::out_of_range(key);
        }

        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            throw std::out_of_range(key);
        }
        return n_attr->value();
    };

    template <> bool attr_if(const XmlNode *n, const char* key)
    {
        if (!n) {
            return false;
        }
        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            return false;
        }
        return stob(std::string(n_attr->value()));
    };

    template <> std::string attr_if(const XmlNode *n, const char* key)
    {
        if (!n) {
            return "";
        }
        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            return "";
        }
        return std::string(n_attr->value());
    }

    template <> const std::string attr_if(const XmlNode *n, const char* key)
    {
        if (!n) {
            return "";
        }
        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            return "";
        }
        return std::string(n_attr->value());
    }

    template <> const char* attr_if(const XmlNode *n, const char* key)
    {
        if (!n) {
            return "";
        }
        rapidxml::xml_attribute<> *n_attr = n->first_attribute(key);
        if (n_attr == nullptr) {
            return "";
        }
        return n_attr->value();
    };

//----/ XML ATTRIBUTES /--------------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      TILED PROJECT LOADING [ DECLARED IN PUBLIC HEADER ]
//------------------------------------------------------------------------------------------------//

    namespace fs = std::filesystem;

    void _sub_search(const fs::directory_entry& root, ResourceTable& rsrc_tbl)
    {
        if (root.is_regular_file()) {
            fs::path fp = root.path();
            const std::string ext = fp.extension().string();
            const std::string name = fp.filename().string();
            const std::string full_path = fp.string();
            if (ext == ".tsx") {
                rsrc_tbl[FileType::Tsx].insert(std::make_pair(name, full_path));
            } else if (ext == ".tmx") {
                rsrc_tbl[FileType::Tmx].insert(std::make_pair(name, full_path));
            } else if (ext == ".png") {
                // to do -- support more image file types
                rsrc_tbl[FileType::Img].insert(std::make_pair(name, full_path));
            }
        } else if (root.is_directory()) {
            for (const fs::directory_entry& dir_entry : fs::recursive_directory_iterator(root)) {
                _sub_search(dir_entry, rsrc_tbl);
            }
        }
    }

    void search(const std::string& root_dir, ResourceTable& rsrc_tbl)
    {
        fs::directory_entry root(root_dir);
        if (!root.is_directory()) {
            printf("Error: cannot search '%s', not a directory.\n", root_dir.c_str());
            ERRCODE = ERR::CODE::BAD_SEARCH_ROOT;
            return;
        }

        rsrc_tbl[FileType::Tsx] = FileMap();
        rsrc_tbl[FileType::Tmx] = FileMap();
        rsrc_tbl[FileType::Img] = FileMap();

        _sub_search(root, rsrc_tbl);
    }

    template <typename T>
    void load(const std::string& filepath, T& dest_obj) {
        // to do -- set error flag
        ERRCODE = ERR::CODE::INVALID_LOAD_OBJECT;
        printf("Error: Invalid or unknown type being loaded '%s'\n", asTypeName<T>());
    }

    template <> void load(const std::string& filepath, Tmx& usr_tmx)
    {
        rapidxml::xml_document<>* doc = new rapidxml::xml_document<>();
        std::string content = "";
        loadXml(filepath, content, doc);
        if (doc == nullptr || content == "") {
            printf("Error loading tmx file: %s\n", filepath.c_str());
            ERRCODE = ERR::CODE::FILE_LOAD_ERROR;
            return;
        }

        XmlNode *map = doc->first_node();
        usr_tmx.width = attr<int>(map, "width");
        usr_tmx.height = attr<int>(map, "height");
        usr_tmx.tilewidth = attr<int>(map, "tilewidth");
        usr_tmx.tileheight = attr<int>(map, "tileheight");

        XmlNode *node = map->first_node();
        while(node) {
            std::string type = std::string(node->name());
            if (type == "tileset") {
                extract<TilesetMap>(node, usr_tmx.tilesets);
            } else if (type == "layer") {
                usr_tmx.layers.push_back(extract<TileLayer>(node, usr_tmx.width, usr_tmx.height));
            } else if (type == "objectgroup") {
                usr_tmx.layers.push_back(extract<ObjectLayer>(node));
            } else if (type == "group") {
                usr_tmx.layers.push_back(extract<GroupedLayer>(node, usr_tmx.width, usr_tmx.height));
            } else {
                printf("Warning: unknown layer type: %s\n", type.c_str());
            }
            node = node->next_sibling();
        }
        delete doc;
    }

    template <> void load(const std::string& filepath, Tsx& usr_tsx)
    {
        rapidxml::xml_document<>* doc = new rapidxml::xml_document<>();
        std::string content = "";
        loadXml(filepath, content, doc);
        if (doc == nullptr || content == "") {
            printf("Error loading tsx file: %s\n", filepath.c_str());
            ERRCODE = ERR::CODE::FILE_LOAD_ERROR;
            return;
        }

        XmlNode *tsx = doc->first_node();

        usr_tsx.name = attr<std::string>(tsx, "name");
        usr_tsx.tilewidth = attr<int>(tsx, "tilewidth");
        usr_tsx.tileheight = attr<int>(tsx, "tileheight");
        usr_tsx.tilecount = attr<int>(tsx, "tilecount");
        usr_tsx.columns = attr<int>(tsx, "columns");

        extract<TileList>(tsx, usr_tsx.tilelist);
        extract<PropertyMap>(tsx, usr_tsx.properties);
        extract<Image>(tsx, usr_tsx.image);

        delete doc;
    }

//----/ TILED PROJECT LOADING /-------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      SIMPLE UTILITY FUNCTIONS
//------------------------------------------------------------------------------------------------//


    bool getTileset(int& indx, tb::Tmx& tmx, const int gid)
    {
        indx = 0; // arbitrary number
        for (auto& [ts_gid, ts] : tmx.tilesets) {
            if (gid >= ts_gid) {
                if (indx < ts_gid) {
                    indx = ts_gid;
                }
            }
        }

        if (indx == 0) {
            ERRCODE = ERR::CODE::NO_TILESET_FOUND;
            return false;
        }
        return true;
    }

    bool getTile(tb::Tile& dest, tb::Tileset& tileset, const int gid)
    {
        if ((size_t) gid >= tileset.tiles.size()) {
            ERRCODE = ERR::CODE::GID_OUT_OF_RANGE;
            return false;
        }
        dest = tileset.tiles.at(gid);
        return true;
    }

//----/ SIMPLE UTILITY FUNCTIONS /----------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      DATA EXTRACTION
//------------------------------------------------------------------------------------------------//

    template <> void extract(const XmlNode *node, Property& prp)
    {
        if (!node) return;
        prp.name = attr_if<std::string>(node, "name");
        prp.type = attr_if<std::string>(node, "type");
        prp.value = attr_if<std::string>(node, "value");
    }

    template <> void extract(const XmlNode* node, TileRect& rect)
    {
        if (!node) return;
        rect.name = attr_if<std::string>(node, "name");
        rect.type = attr_if<std::string>(node, "type");
        rect.id = attr_if<int>(node, "id");
        rect.gid = attr_if<int>(node, "gid");
        rect.x = attr_if<int>(node, "x");
        rect.y = attr_if<int>(node, "y");
        rect.width = attr_if<int>(node, "width");
        rect.height = attr_if<int>(node, "height");
        rect.properties = extract<PropertyMap>(node);
    }

    template <> void extract(const XmlNode* node, TileMap& tile_map)
    {
        if (!node) return;
        XmlNode *og = node->first_node("objectgroup");
        if (!og) {
            return;
        }
        XmlNode *obj = og->first_node("object");
        while(obj != nullptr) {
            tile_map.insert(std::pair<const int, TileRect>(attr<int>(node, "id"), extract<TileRect>(obj)));
            obj = obj->next_sibling();
        }
    };

    template <> void extract(const XmlNode* node, PropertyMap& prp_map)
    {
        if (!node) return;
        XmlNode *prps = node->first_node("properties");
        if (!prps) {
            return;
        }
        XmlNode *n = prps->first_node("property");
        while(n) {
            prp_map.insert(std::pair<const std::string, const Property>(
                attr<const std::string>(n, "name"),
                extract<Property>(n)
            ));
            n = n->next_sibling();
        }
    };

    template <> void extract(const XmlNode* node, Rect& rect)
    {
        if (!node) return;
        rect.x = attr_if<int>(node, "x");
        rect.y = attr_if<int>(node, "y");
        rect.width = attr_if<int>(node, "width");
        rect.height = attr_if<int>(node, "height");
    };

    template <> void extract(const XmlNode* node, RectMap& rect_map)
    {
        if (!node) return;
        XmlNode *og = node->first_node("objectgroup");
        if (!og) {
            return;
        }
        XmlNode *obj = og->first_node("object");
        while(obj != nullptr) {
            rect_map.insert(std::pair<const int, Rect>(attr<int>(node, "id"), extract<Rect>(obj)));
            obj = obj->next_sibling();
        }
    };

    template <> void extract(const XmlNode* node, RectList& rect_list)
    {
        if (!node) return;
        XmlNode *og = node->first_node("objectgroup");
        if (!og) {
            return;
        }
        XmlNode *obj = og->first_node("object");
        while(obj != nullptr) {
            rect_list.push_back(extract<Rect>(obj));
            obj = obj->next_sibling();
        }
    };

    template <> void extract(const XmlNode* node, Image& image)
    {
        if (!node) return;
        XmlNode *img_node = node->first_node("image");
        if (!img_node) {
            return;
        }
        image.source = attr<std::string>(img_node, "source");
        image.width = attr<int>(img_node, "width");
        image.height = attr<int>(img_node, "height");
    };

    template <> void extract(const XmlNode* tile_node, FrameList& frames)
    {
        if (!tile_node) return;
        XmlNode *frame_entry = tile_node->first_node("frame");
        while(frame_entry) {
            frames.push_back({
                attr<int>(frame_entry, "tileid"),
                attr<int>(frame_entry, "duration")
            });
            frame_entry = frame_entry->next_sibling();
        }
    };

    template <> void extract(const XmlNode* node, Wangset& wang_set)
    {
        if (!node) return;
        std::string type = std::string(attr<std::string>(node, "type"));

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

        wang_set.name = attr_if<std::string>(node, "name");
        wang_set.type = type.c_str();
        wang_set.map = map;
    };

    template <> void extract(const XmlNode* node, WangsetList& wangset_list)
    {
        if (!node) return;
        XmlNode *ws = node->first_node("wangsets");
        if (!ws) {
            return;
        }
        for (XmlNode *wn = ws->first_node("wangset"); wn; wn = wn->next_sibling("wangset")) {
            wangset_list.push_back(extract<Wangset>(wn));
        }
    };

    template <> void extract(const XmlNode* node, TileList& tile_list)
    {
        if (!node) return;
        const int columns = attr<int>(node, "columns");
        const int tilewidth = attr<int>(node, "tilewidth");
        const int tileheight = attr<int>(node, "tileheight");
        const int tilecount = attr<int>(node, "tilecount");

        // Create a map of entries in the tileset so we can look up information about the tile later
        // on.
        std::map<const int, XmlNode*> tileset_entries;
        for (XmlNode *tnode = node->first_node("tile"); tnode; tnode = tnode->next_sibling()) {
            if (std::string(tnode->name()) == "tile") {
                tileset_entries.insert(
                    std::pair<const int, XmlNode*>(attr<int>(tnode, "id"), tnode)
                );
            }
        }

        // Iterate through all tiles in this tileset and create a tile entry.
        for (int i = 0; i < tilecount; i ++)
        {
            const int idx = i;

            // Use the tile's position in the tileset (i) + columns in this tileset + tile
            // dimensions to find this tile's texture rectangle
            const TextureRect t_rect {
                (int) idx,
                // x, y, width, height
                idx % columns, idx / columns, tilewidth, tileheight
            };
            // a tileset has no positional data, but we can at least initialize its size
            const Rect p_rect {
                0, 0, tilewidth, tileheight
            };

            // If the tile is in our tileset entry map, then grab the entry so we can include its
            // info.
            XmlNode *tile_entry = nullptr;
            if (tileset_entries.count(i) != 0) {
                tile_entry = tileset_entries.at(i);
            }

            // Create the new tile with any extra details from the tileset entry (if available)
            tile_list.push_back(Tile {
                idx,
                attr_if<std::string>(tile_entry, "type"),
                p_rect,
                t_rect,
                extract<RectList>(tile_entry),
                extract<PropertyMap>(tile_entry),
                extract<FrameList>(tile_entry)
            });
        }
    };

    template <> void extract(const XmlNode* tileset_node, TilesetMap& tileset_map)
    {
        if (!tileset_node) return;
        const int first_gid = attr<int>(tileset_node, "firstgid");
        tileset_map.insert(
            std::pair<const int, const Tileset>(
                first_gid,
                Tileset {
                    first_gid,
                    attr<int>(tileset_node, "tilewidth"),
                    attr<int>(tileset_node, "tileheight"),
                    attr<int>(tileset_node, "tilecount"),
                    attr<int>(tileset_node, "columns"),
                    attr<std::string>(tileset_node, "name"),
                    extract<Image>(tileset_node),
                    extract<TileList>(tileset_node),
                    extract<WangsetList>(tileset_node),
                    extract<PropertyMap>(tileset_node)
                }
            )
        );
    };

    template <> void extract(const XmlNode* lyr_node, TileLayer& tile_lyr, const int tilewidth, const int tileheight)
    {
        if (!lyr_node) return;
        tile_lyr.id = attr<int>(lyr_node, "id"),
        tile_lyr.name = attr<std::string>(lyr_node, "name"),
        tile_lyr.width = attr<int>(lyr_node, "width");
        tile_lyr.height = attr<int>(lyr_node, "height");

        std::vector<int> allgids;
        XmlNode *data = lyr_node->first_node("data");
        split(std::string(data->value()), ',', allgids);

        for (size_t i = 0; i < allgids.size(); i ++) {
            if (allgids[i] == 0) {
                continue;
            }
            tile_lyr.tiles.push_back(TextureRect {
                (int) i,
                allgids[i],
                (int) (i % tile_lyr.width) * tilewidth,
                (int) (i / tile_lyr.width) * tileheight,
                tilewidth,
                tileheight
            });
        }
    };

    template <> void extract(const XmlNode* lyr_node, ObjectLayer& obj_lyr)
    {
        if (!lyr_node) return;
        obj_lyr.id = attr<int>(lyr_node, "id");
        obj_lyr.name = attr<std::string>(lyr_node, "name");
        extract<TileMap>(lyr_node, obj_lyr.tilemap);
    };

    template <> void extract(const XmlNode* lyr_node, GroupedLayer& grp_lyr, const int width, const int height)
    {
        if (!lyr_node) return;
        grp_lyr.id = attr<int>(lyr_node, "id");
        grp_lyr.name = attr<std::string>(lyr_node, "name");
        XmlNode *sub_layer = lyr_node->first_node();
        while(sub_layer) {
            std::string type = std::string(sub_layer->name());
            if (type == "layer") {
                grp_lyr.sublayers.push_back(extract<TileLayer>(sub_layer, width, height));
            } else if (type == "objectgroup") {
                grp_lyr.sublayers.push_back(extract<ObjectLayer>(sub_layer));
            } else if (type == "group") {
                grp_lyr.sublayers.push_back(extract<GroupedLayer>(sub_layer, width, height));
            } else {
                printf("Warning: unknown layer type: %s\n", type.c_str());
            }
            sub_layer = sub_layer->next_sibling();
        }
    };

//----/ DATA EXTRACTION /-------------------------------------------------------------------------//



//------------------------------------------------------------------------------------------------//
//      WANGSET UTILS
//------------------------------------------------------------------------------------------------//

void asSet(const XmlNode* node, WangtileMap& map, WangsetMeta& setmeta)
{
    for (XmlNode *wtile = node->first_node("wangtile"); wtile; wtile = wtile->next_sibling("wangtile"))
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
                std::string(wang_id_str)
            })
        );
    }
}

void asEdgeSet(const XmlNode* node, WangtileMap& map) { asSet(node, map, EdgeSet); };

void asCornerSet(const XmlNode* node, WangtileMap& map) { asSet(node, map, CornerSet); };

void asFullSet(const XmlNode* node, WangtileMap& map) { asSet(node, map, FullSet); };

//----/ WANGSET UTILS /---------------------------------------------------------------------------//

} // namespace tb
