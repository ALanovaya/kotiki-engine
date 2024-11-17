#pragma once

#include <vector>

#include "kotiki-engine/core/movers/mover.hpp"
#include "kotiki-engine/core/trajectory/trajectory.hpp"

namespace mover {
using namespace trajectory;

class TrajectoryMover : public Mover {
private:
    std::unique_ptr<Trajectory> traj_;
    double current_time_;
    double timedelta_;

    void MoveInternal(entity::EntitiesCollection& entities) override;

public:
    TrajectoryMover(std::string const& x_expression, std::string const& y_expression,
                    double timedelta, std::string const& time_var = "t")
        : traj_(std::make_unique<Trajectory>(x_expression, y_expression, time_var)),
          current_time_(0),
          timedelta_(timedelta) {}

    void SetTimedelta(double timedelta) {
        timedelta_ = timedelta;
    }

    void SetTrajectory(std::string const& x_expression, std::string const& y_expression,
                       std::string const& time_var = "t") {
        traj_ = std::make_unique<Trajectory>(x_expression, y_expression, time_var);
        current_time_ = 0.0;
    }
};
}  // namespace mover