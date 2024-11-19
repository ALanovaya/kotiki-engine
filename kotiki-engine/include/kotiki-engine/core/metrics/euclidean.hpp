#pragma once

#include "kotiki-engine/core/metrics/minkowski.hpp"

namespace algo {
class EuclideanMetric : public MinkowskiMetric {
public:
    EuclideanMetric() : MinkowskiMetric(2.0) {}
};
}  // namespace algo
