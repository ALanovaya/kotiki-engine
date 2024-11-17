#pragma once

#include <vector>

#include "kotiki-engine/core/movers/mover.hpp"
#include "kotiki-engine/core/trajectory/trajectory.hpp"

namespace mover {

class TrajectoryMover : public Mover {
private:
    trajectory::Trajectory traj_;
    double current_time_;
    double timedelta_;

    void MoveInternal(entity::EntitiesCollection& entities) override;

public:
    TrajectoryMover(std::string const& x_expression, std::string const& y_expression,
                    double timedelta, std::string const& time_var = "t")
        : traj_(x_expression, y_expression, time_var), current_time_(0), timedelta_(timedelta) {}
};
}  // namespace mover