#pragma once

#include <memory>
#include <vector>

#include "kotiki-engine/core/metrics/metric.hpp"
#include "kotiki-engine/entities/entities_collection.hpp"
#include "kotiki-engine/entities/states.hpp"

namespace algo {
class Algorithm {
protected:
    double R0_;
    double R1_;
    std::shared_ptr<Metric> metric_;

public:
    Algorithm(double R0, double R1, Metric* metric) : R0_(R0), R1_(R1), metric_(metric) {}

    virtual std::vector<entity::EntityState> GetStates(
            entity::EntitiesCollection const& entities) = 0;
};
}  // namespace algo