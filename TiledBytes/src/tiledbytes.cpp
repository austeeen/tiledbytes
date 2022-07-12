#include "core.hpp"

namespace tb
{

uint8_t ERRCODE = ERR::CODE::NONE;
const char *flag = "it works!";

Layer::Layer(const int id, const char* name):
    id(id),
    name(name)
{}

TileLayer::TileLayer(const int id, const char* name, const int w, const int h):
    Layer(id, name),
    width(w),
    height(h)
{}

ObjectLayer::ObjectLayer(const int id, const char* name):
    Layer(id, name)
{}

GroupedLayer::GroupedLayer(const int id, const char* name, const LayerList& sublayers):
    Layer(id, name),
    sublayers(sublayers)
{}

} // namespace tb
