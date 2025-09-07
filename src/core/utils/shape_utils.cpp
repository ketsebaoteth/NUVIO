#include "core/canvas/utils/shape_utils.h"

NUVIO_CANVAS_NAMESPACE_BEGIN

std::ostream& operator<<(std::ostream& os, const Rect& r) {
    os << "Rect { "
       << "pos=(" << r.position.x << ", " << r.position.y << "), "
       << "size=(" << r.size.x << ", " << r.size.y << "), "
       << "left=" << r.edge_position(nuvio::canvas::RectSide::LEFT) << ", "
       << "right=" << r.edge_position(nuvio::canvas::RectSide::RIGHT) << ", "
       << "top=" << r.edge_position(nuvio::canvas::RectSide::TOP) << ", "
       << "bottom=" << r.edge_position(nuvio::canvas::RectSide::BOTTOM)
       << " }";
    return os;
}

NUVIO_CANVAS_NAMESPACE_END
