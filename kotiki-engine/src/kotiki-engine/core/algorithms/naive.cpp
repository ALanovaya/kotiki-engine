#include "kotiki-engine/core/algorithms/naive.hpp"

#include "kotiki-engine/utils/random.hpp"

namespace algo {
std::vector<entity::EntityState> NaiveAlgorithm::GetStates(entity::SceneManager const& scene) {
    auto const& entities_vector = scene.GetEntites();
    std::vector<entity::EntityState> states(entities_vector.size(), entity::EntityState::Calm);

    for (int i = 0; i < entities_vector.size(); ++i) {
        for (int j = 0; j < entities_vector.size(); ++j) {
            if (i == j) {
                continue;
            }
            auto dist = metric_->Calculate(entities_vector[i], entities_vector[j]);
            if (dist <= R0_) {
                states[i] = entity::EntityState::Fighting;
            } else if (dist <= R1_) {
                if (states[i] != entity::EntityState::Fighting &&
                    util::generate_uniform_real() <= 1.0 / dist) {
                    states[i] = entity::EntityState::Angry;
                }
            }
        }
    }

    return states;
}
}  // namespace algo