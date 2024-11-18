#pragma once

#include "kotiki-engine/entities/entities_collection.hpp"

namespace mover {
class Mover {
protected:
    virtual void MoveInternal(entity::EntitiesCollection& entities) = 0;

    static bool FixCoordinates(entity::Entity& entity, FieldParams& field_params);

public:
    virtual void Move(entity::EntitiesCollection& entities) {
        entities.GenerateNewIndices();
        MoveInternal(entities);
    };

    static std::set<int> FixEntityCoordinates(entity::EntitiesCollection& entities);
};
}  // namespace mover