#include "core.hpp"

namespace tb
{

uint8_t ERRCODE = ERR::CODE::NONE;
const char *flag = "it works!";

Layer::Layer(const int id, const char* name):
    id(id),
    name(name)
{}

TileLayer::TileLayer(const int id, const char* name, const int w, const int h, const RectList& tilerects):
    Layer(id, name),
    width(w),
    height(h),
    tilerects(tilerects)
{}

ObjectLayer::ObjectLayer(const int id, const char* name, const RectMap& rects):
    Layer(id, name),
    rects(rects)
{}

GroupedLayer::GroupedLayer(const int id, const char* name, const LayerList& sublayers):
    Layer(id, name),
    sublayers(sublayers)
{}

} // namespace tb
