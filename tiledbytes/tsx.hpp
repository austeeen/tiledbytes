#ifndef TB_TSX_HPP
#define TB_TSX_HPP

#include "common.hpp"


class TileObject: public TsxBaseObject
{
public:
    TileObject(const char* filepath);
    ~TileObject();
    void getProperties(rx::xml_node<>* node);
    void loadConfig(const char *cfg_fp);
    void addTile(rx::xml_node<>* node);
    void addRoll(std::shared_ptr<AnimRoll> roll, rx::xml_node<>* node);

    bool facing_right;
    sf::Texture img_texture;
    std::string img_src;
    int tilecount, columns, totaltiles;
    sf::Vector2i imagesize;
    sf::RenderStates render_states;
    std::map<const int, std::shared_ptr<TileFrame>> tile_tbl;
    std::map<ObjectState, std::shared_ptr<AnimRoll>> animation_rolls;
    std::string cfg_fp;
    PhysicsCoeffs pCoeffs;
    std::string name;
    sf::Vector2i tilesize;
};

#endif // TB_TSX_HPP
