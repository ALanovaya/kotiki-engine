#include <kotiki-engine/core/metrics/euclidean.hpp>

namespace algo {
double EuclideanMetric::Calculate(entity::Entity first, entity::Entity second) {
    return std::sqrt((first.x - second.x) * (first.x - second.x) +
                     (first.y - second.y) * (first.y - second.y));
}
}  // namespace algo