#pragma once

#include <vector>

#include "src/core/movers/mover.h"
#include "src/entities/entity.h"
#include "src/entities/states.h"

namespace algo {
class Algorithm {
public:
    virtual std::vector<entity::EntityState> GetStates(std::vector<entity::Entity> &entities) = 0;
};
}  // namespace algo