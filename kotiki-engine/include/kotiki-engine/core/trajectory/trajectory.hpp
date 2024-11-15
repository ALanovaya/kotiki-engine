#pragma once

#include <matheval.hpp>
#include <stdexcept>
#include <string>
#include <utility>

namespace trajectory {

    class Trajectory {
    private:
        matheval::Parser x_parser_;
        matheval::Parser y_parser_;
        std::string time_var_;

        void ValidateExpression(matheval::Parser& parser, const std::string& time_var) const;

    public:
        Trajectory(const std::string& x_expression, const std::string& y_expression, const std::string& time_var = "t");

        std::pair<double, double> GetPosition(std::pair<double, double> start_coordinates, double t);
    };

}  // namespace trajectory
