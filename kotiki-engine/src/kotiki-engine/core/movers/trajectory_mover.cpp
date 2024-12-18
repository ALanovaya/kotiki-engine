#include "kotiki-engine/core/movers/trajectory_mover.hpp"

namespace mover {
void TrajectoryMover::MoveInternal(entity::SceneManager& scene) {
    current_time_ += timedelta_;
    for (auto index : scene.GetIndices()) {
        auto& entity = scene.GetEntites()[index];
        auto& start_coordinates = scene.GetStartCoordinates()[index];
        auto [x, y] = traj_->GetPosition(start_coordinates, current_time_);
        entity.x = x;
        entity.y = y;
    }
}
}  // namespace mover