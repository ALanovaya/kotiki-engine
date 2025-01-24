#pragma once

#include "kotiki-engine/core/metrics/metric.hpp"
#include "kotiki-engine/entities/entity.hpp"

namespace algo {

// Chebyshev distance metric class
// https://en.wikipedia.org/wiki/Chebyshev_distance
class ChebyshevMetric : public Metric {
public:
    ChebyshevMetric() = default;

    coord_t Calculate(entity::Entity first, entity::Entity second);
};
}  // namespace algo
