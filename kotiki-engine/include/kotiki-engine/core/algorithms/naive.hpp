#pragma once

#include "kotiki-engine/core/algorithms/algorithm.hpp"

namespace algo {
class NaiveAlgorithm : public Algorithm {
public:
    NaiveAlgorithm(coord_t R0, coord_t R1, Metric* metric) : Algorithm(R0, R1, metric) {};
    std::vector<entity::EntityState> GetStates(entity::EntitiesCollection const& entities);
};
}  // namespace algo