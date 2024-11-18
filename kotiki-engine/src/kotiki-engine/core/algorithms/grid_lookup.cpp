#include "kotiki-engine/core/algorithms/grid_lookup.hpp"

namespace algo {
std::vector<entity::EntityState> GridLookupAlgorithm::GetStates(
        entity::EntitiesCollection const& entities) {
    std::vector<entity::EntityState> states(entities.GetNumberOfEntities(),
                                            entity::EntityState::Calm);
    int cell_count_x = static_cast<int>(static_cast<coord_t>(entities.GetFieldParams().w) / R1_);
    int cell_count_y = static_cast<int>(static_cast<coord_t>(entities.GetFieldParams().h) / R1_);

    grid_.clear();
    grid_.resize(cell_count_x * cell_count_y, {});
    auto const& field_params = entities.GetFieldParams();
    auto const& entities_vector = entities.GetEntites();

    for (int i = 0; i < entities.GetNumberOfEntities(); ++i) {
        auto const& entity = entities_vector[i];
        int cell_x = static_cast<int>((entity.x - field_params.x) / R1_);
        int cell_y = static_cast<int>((entity.y - field_params.y) / R1_);
        grid_[cell_x * cell_count_x + cell_y].push_back(i);
    }

    for (auto index : entities.GetIndices()) {
        auto const& entity = entities_vector[index];
        int cell_x = static_cast<int>((entity.x - field_params.x) / R1_);
        int cell_y = static_cast<int>((entity.y - field_params.y) / R1_);

        for (int offset_x = -1; offset_x < 2; ++offset_x) {
            if (cell_x + offset_x < 0 || cell_x + offset_x >= cell_count_x) {
                continue;
            }
            for (int offset_y = -1; offset_y < 2; ++offset_y) {
                if (cell_y + offset_y < 0 || cell_y + offset_y >= cell_count_y) {
                    continue;
                }
                auto const& neigh_cell =
                        grid_[(cell_x + offset_x) * cell_count_x + cell_y + offset_y];
                for (auto neigh_index : neigh_cell) {
                    if (neigh_index == index) {
                        continue;
                    }
                    auto const& neigh_entitiy = entities_vector[neigh_index];
                    auto dist = metric_->Calculate(entity, neigh_entitiy);
                    if (dist <= R0_) {
                        states[index] = entity::EntityState::Fighting;
                        states[neigh_index] = entity::EntityState::Fighting;
                    } else if (dist <= R1_) {
                        if (states[index] != entity::EntityState::Fighting &&
                            util::generate_uniform_real() <= 1.0 / dist) {
                            states[index] = entity::EntityState::Angry;
                        }
                        if (states[neigh_index] != entity::EntityState::Fighting &&
                            util::generate_uniform_real() <= 1.0 / dist) {
                            states[neigh_index] = entity::EntityState::Angry;
                        }
                    }
                }
            }
        }
    }

    return states;
}
}  // namespace algo