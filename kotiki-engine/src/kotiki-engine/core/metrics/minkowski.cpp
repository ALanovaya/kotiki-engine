#include <stdexcept>
#include "kotiki-engine/core/metrics/minkowski.hpp"

namespace algo {
MinkowskiMetric::MinkowskiMetric(double p) {
    if (p <= 0) {
        throw std::invalid_argument("Argument p must be greater than 0");
    }
    p_ = p;
}

coord_t MinkowskiMetric::Calculate(entity::Entity first, entity::Entity second) {
    double diff_x = std::abs(first.x - second.x);
    double diff_y = std::abs(first.y - second.y);

    double sum = std::pow(diff_x, p_) + std::pow(diff_y, p_);

    return std::pow(sum, 1.0 / p_);
}
}  // namespace algo
