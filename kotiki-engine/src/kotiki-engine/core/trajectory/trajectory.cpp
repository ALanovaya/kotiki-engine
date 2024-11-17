#include <kotiki-engine/core/trajectory/trajectory.hpp>

namespace trajectory {
Trajectory::Trajectory(std::string const& x_expression, std::string const& y_expression,
                       std::string const& time_var)
    : time_var_(time_var) {
    x_parser_.parse(x_expression);
    ValidateExpression(x_parser_, time_var_);
    y_parser_.parse(y_expression);
    ValidateExpression(y_parser_, time_var_);
}

void Trajectory::ValidateExpression(matheval::Parser& parser, std::string const& time_var) const {
    auto variables = parser.find_variables();
    for (auto const& variable : variables) {
        if (variable != time_var) {
            throw std::invalid_argument("Expression contains unexpected variable: " + variable);
        }
    }
}

std::pair<coord_t, coord_t> Trajectory::GetPosition(std::pair<coord_t, coord_t> start_coordinates,
                                                    double t) {
    coord_t x = start_coordinates.first + x_parser_.evaluate({std::make_pair(time_var_, t)});
    coord_t y = start_coordinates.second + y_parser_.evaluate({std::make_pair(time_var_, t)});
    return {x, y};
}
}  // namespace trajectory
