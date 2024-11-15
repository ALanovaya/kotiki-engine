#include <kotiki-engine/core/trajectory/trajectory.hpp>

namespace trajectory {
Trajectory::Trajectory(const std::string& x_expression, const std::string& y_expression, const std::string& time_var)
        : time_var_(time_var) {
    x_parser_.parse(x_expression);
    ValidateExpression(x_parser_, time_var_);
    y_parser_.parse(y_expression);
    ValidateExpression(y_parser_, time_var_);
}

void Trajectory::ValidateExpression(matheval::Parser& parser, const std::string& time_var) const {
    auto variables = parser.find_variables();
    for (const auto& variable : variables) {
        if (variable != time_var) {
            throw std::invalid_argument("Expression contains unexpected variable: " + variable);
        }
    }
}

std::pair<double, double> Trajectory::GetPosition(std::pair<double, double> start_coordinates,
                                                  double t) {
    double x = start_coordinates.first + x_parser_.evaluate({std::make_pair(time_var_, t)});
    double y = start_coordinates.second + y_parser_.evaluate({std::make_pair(time_var_, t)});
    return {x, y};
}
}  // namespace trajectory
