#pragma once

#include <vector>

#include "src/core/movers/mover.h"
#include "src/entities/entity.h"
#include "src/entities/states.h"

namespace algo {
class Algorithm {
protected:
    std::vector<entity::Entity> entities_;
    mover::Mover* mover_;

    virtual void UpdateStates() = 0;

public:
    Algorithm(std::vector<entity::Entity> entities, mover::Mover* mover)
        : entities_(entities), mover_(mover) {};

    void MoveEntities() {
        mover_->Move(entities_);
        UpdateStates();
    }

    virtual std::vector<entity::Entity>& GetEntities() {
        return entities_;
    };
};
}  // namespace algo