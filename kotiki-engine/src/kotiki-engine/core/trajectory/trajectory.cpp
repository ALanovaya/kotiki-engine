#include <matheval.hpp>
#include <kotiki-engine/core/trajectory/trajectory.hpp>

namespace trajectory {
std::pair<double, double> Trajectory::GetPosition(std::pair<double, double> start_coordinates, double t) {
    double x = start_coordinates.first + x_parser_.evaluate({std::make_pair(time_var_, t)});
    double y = start_coordinates.second + y_parser_.evaluate({std::make_pair(time_var_, t)});
    return {x, y};
}
} // namespace trajectory
