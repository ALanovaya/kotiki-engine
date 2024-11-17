#pragma once

#include <memory>
#include <vector>

#include "kotiki-engine/core/metrics/metric.hpp"
#include "kotiki-engine/entities/entities_collection.hpp"
#include "kotiki-engine/entities/states.hpp"
#include "kotiki-engine/utils/types.h"

namespace algo {
class Algorithm {
protected:
    coord_t R0_;
    coord_t R1_;
    std::shared_ptr<Metric> metric_;

public:
    Algorithm(coord_t R0, coord_t R1, Metric* metric) : R0_(R0), R1_(R1), metric_(metric) {}

    virtual std::vector<entity::EntityState> GetStates(
            entity::EntitiesCollection const& entities) = 0;
};
}  // namespace algo