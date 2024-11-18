#include <algorithm>
#include <cmath>
#include "kotiki-engine/core/metrics/chebyshev.hpp"

namespace algo {
coord_t ChebyshevMetric::Calculate(entity::Entity first, entity::Entity second) {
    coord_t diff_x = std::abs(first.x - second.x);
    coord_t diff_y = std::abs(first.y - second.y);

    return std::max(diff_x, diff_y);
}
}  // namespace algo
