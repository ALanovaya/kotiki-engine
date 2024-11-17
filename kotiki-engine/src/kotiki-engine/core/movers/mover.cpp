#include "kotiki-engine/core/movers/mover.hpp"

namespace mover {
void Mover::FixCoordinates(entity::Entity& entity, FieldParams& field_params) {
    while (entity.x < field_params.x) {
        entity.x += field_params.x;
    }
    while (entity.x > field_params.x + field_params.w) {
        entity.x -= field_params.x + field_params.w;
    }
    while (entity.y < field_params.y) {
        entity.y += field_params.y;
    }
    while (entity.y > field_params.y + field_params.h) {
        entity.y -= field_params.y + field_params.h;
    }
}
}  // namespace mover