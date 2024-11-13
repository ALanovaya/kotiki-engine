#include <kotiki-engine/core/algorithms/naive.hpp>
#include <kotiki-engine/utils/random.hpp>

namespace algo {
std::vector<entity::EntityState> NaiveAlgorithm::GetStates(std::vector<entity::Entity>& entities) {
    std::vector<entity::EntityState> states(entities.size(), entity::EntityState::Calm);

    for (int i = 0; i < entities.size(); ++i) {
        for (int j = 0; j < entities.size(); ++j) {
            if (i == j) {
                continue;
            }
            auto dist = metric_->Calculate(entities[i], entities[j]);
            if (dist <= R0_) {
                states[i] = entity::EntityState::Fighting;
            } else if (dist <= R1_) {
                if (states[i] != entity::EntityState::Fighting && sample_uniform() <= 1.0 / dist) {
                    states[i] = entity::EntityState::Angry;
                }
            }
        }
    }

    return states;
}
}  // namespace algo