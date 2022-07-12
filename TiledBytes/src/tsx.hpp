#ifndef TB_TSX_HPP
#define TB_TSX_HPP

#include "core.hpp"
#include "utils.hpp"
#include "extractors.hpp"

namespace tb
{

void newImageSource(XmlNode* node, Image& image);

void getTileList(XmlNode* node, Tsx& usr_tsx);

void newAnimation(XmlNode* node, Tsx& usr_tsx, const int id);


} // namespace tb

#endif // TB_TSX_HPP
