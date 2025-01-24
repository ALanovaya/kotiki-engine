#pragma once

#include "kotiki-engine/core/metrics/minkowski.hpp"

namespace algo {

// Euclidean distance metric class
// https://en.wikipedia.org/wiki/Euclidean_distance
class EuclideanMetric : public MinkowskiMetric {
public:
    EuclideanMetric() : MinkowskiMetric(2.0) {}
};
}  // namespace algo
