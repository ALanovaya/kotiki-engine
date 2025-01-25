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
            UpdateStates(entities_vector, states, i, j);
        }
    }

    return states;
}
}  // namespace algo