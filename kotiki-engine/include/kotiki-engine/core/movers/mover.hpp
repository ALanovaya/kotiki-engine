#pragma once

#include "kotiki-engine/entities/scene_manager.hpp"

namespace mover {
class Mover {
protected:
    virtual void MoveInternal(entity::SceneManager& scene) = 0;

    static bool FixCoordinates(entity::Entity& entity, FieldParams& field_params);

public:
    virtual void Move(entity::SceneManager& scene) {
        scene.GenerateNewIndices();
        MoveInternal(scene);
    };

    static std::set<int> FixEntityCoordinates(entity::SceneManager& scene);
};
}  // namespace mover