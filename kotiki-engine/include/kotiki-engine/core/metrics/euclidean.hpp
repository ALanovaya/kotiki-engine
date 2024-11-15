#pragma once

#include <cmath>

#include "kotiki-engine/core/metrics/metric.hpp"

namespace algo {
class EuclideanMetric : public Metric {
    double Calculate(entity::Entity first, entity::Entity second);
};
}  // namespace algo