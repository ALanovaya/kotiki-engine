#pragma once

#include <vector>

#include "kotiki-engine/core/movers/mover.hpp"
#include "kotiki-engine/core/trajectory/trajectory.hpp"

namespace mover {
using namespace trajectory;

// Trajectory mover class
// Moves entities across parsed trajectory
class TrajectoryMover : public Mover {
private:
    std::unique_ptr<Trajectory> traj_;  // Trajectory
    double current_time_;               // Current time for position calculation
    double timedelta_;                  // Time step

    void MoveInternal(entity::SceneManager& scene) override;

public:
    /**
     * Trajectory Mover constructor
     *
     * @param x_expression Expression of x coordinate
     * @param y_expression Expression of y coordinate
     * @param timedelta Time step
     * @param time_var Variable to define time variable in expressions above
     */
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