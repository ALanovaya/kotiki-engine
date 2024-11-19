#pragma once

#include "kotiki-engine/core/metrics/metric.hpp"
#include "kotiki-engine/entities/entity.hpp"
#include <cmath>

namespace algo {
class MinkowskiMetric : public Metric {
public:
    MinkowskiMetric(double p);
    coord_t Calculate(entity::Entity first, entity::Entity second) override;

private:
    double p_;
};
}  // namespace algo
