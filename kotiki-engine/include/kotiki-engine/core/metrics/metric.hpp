#pragma once

#include "kotiki-engine/entities/entity.hpp"

namespace algo {
// Base class for distance metric
class Metric {
public:
    /**
     * Calculates distance between two entities
     *
     * @param first First entity
     * @param second Second entity
     * @return Distance between two entities
     */
    virtual coord_t Calculate(entity::Entity first, entity::Entity second) = 0;
};
}  // namespace algo