#pragma once

#include <matheval.hpp>
#include <stdexcept>
#include <string>

namespace trajectory {
class Trajectory {
private:
    matheval::Parser x_parser_;
    matheval::Parser y_parser_;
    std::string time_var_;

    void ValidateExpression(matheval::Parser& parser, const std::string& time_var) const {
        auto variables = parser.find_variables();
        for (const auto& variable : variables) {
            if (variable != time_var) {
                throw std::invalid_argument("Expression contains unexpected variable: " + variable);
            }
        }
    }

public:
    Trajectory(std::string const& x_expression, std::string const& y_expression,
               std::string const& time_var = "t")
        : time_var_(time_var) {
        x_parser_.parse(x_expression);
        ValidateExpression(x_parser_, time_var_);
        y_parser_.parse(y_expression);
        ValidateExpression(y_parser_, time_var_);
    };

    std::pair<double, double> GetPosition(std::pair<double, double> start_coordinates, double t);
};
}  // namespace trajectory
