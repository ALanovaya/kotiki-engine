#pragma once

#include "kotiki-engine/core/metrics/minkowski.hpp"

namespace algo {
class ManhattanMetric : public MinkowskiMetric {
public:
    ManhattanMetric() : MinkowskiMetric(1.0) {}
};
}  // namespace algo
