#pragma once

#include <memory>
#include <vector>

#include "kotiki-engine/core/metrics/metric.hpp"
#include "kotiki-engine/entities/scene_manager.hpp"
#include "kotiki-engine/entities/states.hpp"
#include "kotiki-engine/utils/types.h"

namespace algo {

// Base algorithm class
class Algorithm {
protected:
    coord_t R0_;  // Distance threshold for fighting state
    coord_t R1_;  // Distance threshold for angry state
    std::unique_ptr<Metric> metric_;

public:
    Algorithm(coord_t R0, coord_t R1, std::unique_ptr<Metric>&& metric)
        : R0_(R0), R1_(R1), metric_(std::move(metric)) {}

    /**
     * Get states of entities on current scene
     *
     * @param scene Current scene
     * @return Vector of new states of entities on scene
     */
    virtual std::vector<entity::EntityState> GetStates(entity::SceneManager const& scene) = 0;

        virtual void SetR0(coord_t R0) {
        R0_ = R0;
    }

    virtual void SetR1(coord_t R1) {
        R1_ = R1;
    }

    virtual void SetMetric(std::unique_ptr<Metric>&& metric) {
        metric_ = std::move(metric);
    }
};
}  // namespace algo