#pragma once

#include <matheval.hpp>

namespace trajectory {
    class Trajectory {
    private:
        matheval::Parser x_parser_;
        matheval::Parser y_parser_;
        std::string time_var_;

    public:
        Trajectory(const std::string& x_expression, const std::string& y_expression, const std::string& time_var = "t") : time_var_(time_var) {
            x_parser_.parse(x_expression);
            y_parser_.parse(y_expression);
        };

        std::pair<double, double> GetPosition(std::pair<double, double> start_coordinates, double t);
    };
} // namespace trajectory
