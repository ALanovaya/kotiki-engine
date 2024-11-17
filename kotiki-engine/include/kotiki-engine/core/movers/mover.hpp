#pragma once

#include <vector>

#include "kotiki-engine/entities/entities_collection.hpp"

namespace mover {
class Mover {
protected:
    virtual void MoveInternal(entity::EntitiesCollection& entities) = 0;

    static void FixCoordinates(entity::Entity& entity, FieldParams& field_params);

public:
    virtual void Move(entity::EntitiesCollection& entities) {
        MoveInternal(entities);
        entities.GenerateNewIndices();
    };
};
}  // namespace mover