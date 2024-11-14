#pragma once

#include <matheval.hpp>

namespace trajectory {
class Trajectory {
private:
    matheval::Parser x_parser_;
    matheval::Parser y_parser_;
    std::string time_var_;

public:
    Trajectory(std::string const& x_expression, std::string const& y_expression,
               std::string const& time_var = "t")
        : time_var_(time_var) {
        x_parser_.parse(x_expression);
        y_parser_.parse(y_expression);
    };

    std::pair<double, double> GetPosition(std::pair<double, double> start_coordinates, double t);
};
}  // namespace trajectory
