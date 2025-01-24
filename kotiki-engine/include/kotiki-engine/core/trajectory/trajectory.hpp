#pragma once

#include <matheval.hpp>
#include <stdexcept>
#include <string>
#include <utility>

#include "kotiki-engine/utils/types.h"

namespace trajectory {

// Trajectory class
// Is being used to calculate positions of entities moving according to some trajectory
class Trajectory {
private:
    matheval::Parser x_parser_;  // Parser for x expression
    matheval::Parser y_parser_;  // Parser for y expression
    std::string time_var_;       // Time variable

    void ValidateExpression(matheval::Parser& parser, std::string const& time_var) const;

public:
    /**
     * Trajectory constructor
     *
     * @param x_expression Expression of x coordinate
     * @param y_expression Expression of y coordinate
     * @param time_var Variable to define time variable in expressions above
     */
    Trajectory(std::string const& x_expression, std::string const& y_expression,
               std::string const& time_var = "t");
    /**
     * Get position in cirrent time
     *
     * @param start_coordinates Start coordinates of entity
     * @param t Current time
     * @return Current coordinates in time "t"
     */
    std::pair<coord_t, coord_t> GetPosition(std::pair<coord_t, coord_t> start_coordinates,
                                            double t);
};

}  // namespace trajectory
