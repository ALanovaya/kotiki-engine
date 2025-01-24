#pragma once

#include "kotiki-engine/core/metrics/minkowski.hpp"

namespace algo {

// Manhattan distance metric class
// https://en.wikipedia.org/wiki/Taxicab_geometry
class ManhattanMetric : public MinkowskiMetric {
public:
    ManhattanMetric() : MinkowskiMetric(1.0) {}
};
}  // namespace algo
