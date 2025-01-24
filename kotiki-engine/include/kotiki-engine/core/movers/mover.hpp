#pragma once

#include "kotiki-engine/entities/scene_manager.hpp"

namespace mover {

// Base Mover class
class Mover {
protected:
    /**
     * Moves entities according to mover rules
     *
     * @param scene Current scene
     */
    virtual void MoveInternal(entity::SceneManager& scene) = 0;

    /**
     * Fix entity coordinates to fit into scene
     *
     * @param entity Entity on a scene
     * @param field_params Parameters of a scene
     * @return True if coordinates were changed, false overwise
     */
    static bool FixCoordinates(entity::Entity& entity, entity::FieldParams& field_params);

public:
    /**
     * Moves entities on a scene with generating new moving indices each time
     *
     * @param scene Current scene
     */
    virtual void Move(entity::SceneManager& scene) {
        scene.GenerateNewIndices();
        MoveInternal(scene);
    };

    /**
     * Fix coordinates of all entities on a scene according to mover rules
     *
     * @param scene Current scene
     * @return Set of indices of entities with fixed coordinates
     */
    static std::set<int> FixEntityCoordinates(entity::SceneManager& scene);
};
}  // namespace mover