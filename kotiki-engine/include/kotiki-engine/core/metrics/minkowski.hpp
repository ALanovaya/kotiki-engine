#pragma once

#include <cmath>

#include "kotiki-engine/core/metrics/metric.hpp"
#include "kotiki-engine/entities/entity.hpp"

namespace algo {

// Minkowski distance metric class
// https://en.wikipedia.org/wiki/Minkowski_distance
class MinkowskiMetric : public Metric {
public:
    MinkowskiMetric(double p);
    coord_t Calculate(entity::Entity first, entity::Entity second) override;

private:
    double p_;  // Parameter of Minkowski metric
};
}  // namespace algo
