#pragma once

#include <memory>
#include <vector>

#include "src/core/metrics/metric.hpp"
#include "src/entities/entity.hpp"
#include "src/entities/states.hpp"

namespace algo {
class Algorithm {
protected:
    double r_;
    std::unique_ptr<Metric> metric_;

public:
    Algorithm(double r, Metric* metric) : r_(r), metric_(metric) {}

    virtual std::vector<entity::EntityState> GetStates(std::vector<entity::Entity>& entities) = 0;
};
}  // namespace algo