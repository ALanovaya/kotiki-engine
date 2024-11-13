#pragma once

#include "matheval.hpp"

namespace trajectory {
class Trajectory {
private:
    std::string x_expression_;
    std::string y_expression_;
    std::string time_var_;

public:
    Trajectory(const std::string& x_expression, const std::string& y_expression, const std::string& time_var = "t")
            : x_expression_(x_expression), y_expression_(y_expression), time_var_(time_var) {};

    virtual std::pair<double, double> GetPosition(std::pair<double, double> start_coordinates, double t);
};
} // namespace trajectory
