#include "kotiki-engine/core/algorithms/grid_lookup.hpp"

#include <stdexcept>

namespace algo {
std::vector<entity::EntityState> GridLookupAlgorithm::GetStates(entity::SceneManager const& scene) {
    std::vector<entity::EntityState> states(scene.GetNumberOfEntities(), entity::EntityState::Calm);

    // Step 1. Initialize grid cells
    int cell_count_x =
            static_cast<int>(std::floor(static_cast<coord_t>(scene.GetFieldParams().w) / R1_)) + 1;
    int cell_count_y =
            static_cast<int>(std::floor(static_cast<coord_t>(scene.GetFieldParams().h) / R1_)) + 1;

    grid_ = std::vector<std::vector<int>>(cell_count_x * cell_count_y, std::vector<int>(0));
    auto const& field_params = scene.GetFieldParams();
    auto const& entities_vector = scene.GetEntites();

    for (int i = 0; i < scene.GetNumberOfEntities(); ++i) {
        auto const& entity = entities_vector[i];
        if (entity.x < field_params.x || entity.x > field_params.x + field_params.w ||
            entity.y < field_params.y || entity.y > field_params.y + field_params.h) {
            throw std::invalid_argument(
                    "Some entities are out of field, impossible to use grid lookup algorithm.");
        }
        int cell_x = static_cast<int>(std::floor((entity.x - field_params.x) / R1_));
        int cell_y = static_cast<int>(std::floor((entity.y - field_params.y) / R1_));
        grid_[cell_x * cell_count_y + cell_y].push_back(i);
    }

    // Step 2. Calculate states of entities using previously initialized grid
    // Only moved entities are being processed
    for (auto index : scene.GetIndices()) {
        auto const& entity = entities_vector[index];

        // Cell coordinates of current entity
        int cell_x = static_cast<int>(std::floor((entity.x - field_params.x) / R1_));
        int cell_y = static_cast<int>(std::floor((entity.y - field_params.y) / R1_));

        // Find neigbours in adjacent cells
        for (int offset_x = -1; offset_x < 2; ++offset_x) {
            if (cell_x + offset_x < 0 || cell_x + offset_x >= cell_count_x) {
                continue;
            }
            for (int offset_y = -1; offset_y < 2; ++offset_y) {
                if (cell_y + offset_y < 0 || cell_y + offset_y >= cell_count_y) {
                    continue;
                }
                auto const& neigh_cell =
                        grid_[(cell_x + offset_x) * cell_count_y + cell_y + offset_y];
                for (auto neigh_index : neigh_cell) {
                    if (neigh_index == index) {
                        continue;
                    }
                    UpdateStates(entities_vector, states, index, neigh_index);
                }
            }
        }
    }

    return states;
}
}  // namespace algo