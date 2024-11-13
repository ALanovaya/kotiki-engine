#pragma once

#include "matheval.hpp"
#include <kotiki-engine/core/trajectory/trajectory.hpp>

namespace trajectory {
std::pair<double, double> Trajectory::GetPosition(std::pair<double, double> start_coordinates, double t) {
    matheval::Parser x_parser;
    x_parser.parse(Trajectory::x_expression_);
    double x = start_coordinates.first + x_parser.evaluate({std::make_pair(Trajectory::time_var_, t)});

    matheval::Parser y_parser;
    y_parser.parse(Trajectory::y_expression_);
    double y = start_coordinates.second + y_parser.evaluate({std::make_pair(Trajectory::time_var_, t)});

    return {x, y};
}
} // namespace trajectory
