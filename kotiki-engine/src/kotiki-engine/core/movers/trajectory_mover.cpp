#include "kotiki-engine/core/movers/trajectory_mover.hpp"

namespace mover {
void TrajectoryMover::MoveInternal(entity::EntitiesCollection& entities) {
    current_time_ += timedelta_;
    for (auto index : entities.GetIndices()) {
        auto& entity = entities.GetEntites()[index];
        auto& start_coordinates = entities.GetStartCoordinates()[index];
        auto [x, y] = traj_->GetPosition(start_coordinates, current_time_);
        entity.x = x;
        entity.y = y;

        FixCoordinates(entity, entities.GetFieldParams());
    }
}
}  // namespace mover