#pragma once

#include <matheval.hpp>
#include <stdexcept>
#include <string>
#include <utility>

#include "kotiki-engine/utils/types.h"

namespace trajectory {

class Trajectory {
private:
    matheval::Parser x_parser_;
    matheval::Parser y_parser_;
    std::string time_var_;

    void ValidateExpression(matheval::Parser& parser, std::string const& time_var) const;

public:
    Trajectory(std::string const& x_expression, std::string const& y_expression,
               std::string const& time_var = "t");

    std::pair<coord_t, coord_t> GetPosition(std::pair<coord_t, coord_t> start_coordinates,
                                            double t);
};

}  // namespace trajectory
