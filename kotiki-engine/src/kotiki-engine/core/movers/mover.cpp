#include "kotiki-engine/core/movers/mover.hpp"

namespace mover {
bool Mover::FixCoordinates(entity::Entity& entity, FieldParams& field_params) {
    bool changed = false;
    while (entity.x < field_params.x) {
        entity.x += field_params.w;
        changed = true;
    }
    while (entity.x > field_params.x + field_params.w) {
        entity.x -= field_params.w;
        changed = true;
    }
    while (entity.y < field_params.y) {
        entity.y += field_params.h;
        changed = true;
    }
    while (entity.y > field_params.y + field_params.h) {
        entity.y -= field_params.h;
        changed = true;
    }
    return changed;
}

std::set<int> Mover::FixEntityCoordinates(entity::SceneManager& scene) {
    std::set<int> indices;
    for (auto index : scene.GetIndices()) {
        auto& entity = scene.GetEntites()[index];
        if (Mover::FixCoordinates(entity, scene.GetFieldParams())) {
            indices.insert(index);
        }
    }
    return indices;
}
}  // namespace mover