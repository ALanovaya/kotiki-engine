#pragma once

#include "kotiki-engine/core/algorithms/algorithm.hpp"

namespace algo {
class NaiveAlgorithm : public Algorithm {
public:
    NaiveAlgorithm(coord_t R0, coord_t R1, std::unique_ptr<Metric>&& metric)
        : Algorithm(R0, R1, std::move(metric)) {};
    std::vector<entity::EntityState> GetStates(entity::SceneManager const& scene) override;
};
}  // namespace algo