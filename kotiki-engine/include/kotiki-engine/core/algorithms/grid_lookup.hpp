#pragma once

#include "kotiki-engine/core/algorithms/algorithm.hpp"

namespace algo {

// Grid lookup algorithm implementation
// https://www.gorillasun.de/blog/particle-system-optimization-grid-lookup-spatial-hashing/
class GridLookupAlgorithm : public Algorithm {
private:
    std::vector<std::vector<int>> grid_;  // Grid, essential for this algorithm

public:
    GridLookupAlgorithm(coord_t R0, coord_t R1, std::unique_ptr<Metric>&& metric)
        : Algorithm(R0, R1, std::move(metric)) {};
    std::vector<entity::EntityState> GetStates(entity::SceneManager const& scene) override;
};
}  // namespace algo