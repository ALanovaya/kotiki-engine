#include "kotiki-engine/core/algorithms/algorithm.hpp"

namespace algo {
void Algorithm::UpdateStates(std::vector<entity::Entity> const& entities,
                             std::vector<entity::EntityState>& states, std::size_t i,
                             std::size_t j) {
    auto dist = metric_->Calculate(entities[i], entities[j]);
    if (dist <= R0_) {
        states[i] = entity::EntityState::Fighting;
        states[j] = entity::EntityState::Fighting;
        return;
    }
    if (dist <= R1_) {
        if (states[i] != entity::EntityState::Fighting &&
            util::generate_uniform_real() <= 1.0 / dist) {
            states[i] = entity::EntityState::Angry;
        }
        if (states[j] != entity::EntityState::Fighting &&
            util::generate_uniform_real() <= 1.0 / dist) {
            states[j] = entity::EntityState::Angry;
        }
    }
}
}  // namespace algo