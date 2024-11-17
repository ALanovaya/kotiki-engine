#pragma once

#include <vector>

#include "kotiki-engine/entities/entities_collection.hpp"

namespace mover {
class Mover {
private:
    virtual void MoveInternal(entity::EntitiesCollection& entities) = 0;

public:
    virtual void Move(entity::EntitiesCollection& entities) {
        MoveInternal(entities);
        entities.GenerateNewIndices();
    };
};
}  // namespace mover