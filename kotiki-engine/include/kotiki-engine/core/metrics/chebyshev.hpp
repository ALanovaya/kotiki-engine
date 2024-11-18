#pragma once

#include "kotiki-engine/core/metrics/metric.hpp"
#include "kotiki-engine/entities/entity.hpp"

namespace algo {
class ChebyshevMetric : public Metric {
public:
    ChebyshevMetric() = default;

    coord_t Calculate(entity::Entity first, entity::Entity second);
};
}  // namespace algo
