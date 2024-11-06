#pragma once

#include <kotiki-engine/core/metrics/metric.hpp>
#include <kotiki-engine/entities/entity.hpp>
#include <kotiki-engine/entities/states.hpp>
#include <memory>
#include <vector>

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