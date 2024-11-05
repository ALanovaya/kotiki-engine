#pragma once

#include <vector>

#include "src/core/metrics/metric.h"
#include "src/entities/entity.h"
#include "src/entities/states.h"

namespace algo {
class Algorithm {
protected:
    double r_;
    Metric* metric_;

public:
    Algorithm(double r, Metric* metric) : r_(r), metric_(metric) {}

    virtual std::vector<entity::EntityState> GetStates(std::vector<entity::Entity>& entities) = 0;
};
}  // namespace algo