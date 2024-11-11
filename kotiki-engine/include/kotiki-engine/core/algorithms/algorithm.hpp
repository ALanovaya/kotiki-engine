#pragma once

#include <kotiki-engine/core/metrics/metric.hpp>
#include <kotiki-engine/entities/entity.hpp>
#include <kotiki-engine/entities/states.hpp>
#include <memory>
#include <vector>

namespace algo {
class Algorithm {
protected:
    double R0_;
    double R1_;
    std::shared_ptr<Metric> metric_;

public:
    Algorithm(double R0, double R1, Metric* metric) : R0_(R0), R1_(R1), metric_(metric) {}

    virtual std::vector<entity::EntityState> GetStates(std::vector<entity::Entity>& entities) = 0;
};
}  // namespace algo