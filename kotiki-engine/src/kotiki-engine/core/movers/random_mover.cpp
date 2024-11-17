#include "kotiki-engine/core/movers/random_mover.hpp"

#include <stdexcept>

#include "kotiki-engine/utils/random.hpp"

namespace mover {
RandomMover::RandomMover(double min_step, double max_step) {
    if (max_step < min_step) {
        throw std::invalid_argument(
                "In Random Mover minimal step must be less or equal to maximal step");
    }

    min_step_ = min_step;
    max_step_ = max_step;
}

void RandomMover::MoveInternal(entity::EntitiesCollection& entities) {
    for (auto index : entities.GetIndices()) {
        auto& entity = entities.GetEntites()[index];
        int x_sign = util::generate_uniform_real() > 0.5 ? 1 : -1;
        int y_sign = util::generate_uniform_real() > 0.5 ? 1 : -1;

        entity.x += (min_step_ + util::generate_uniform_real() * (max_step_ - min_step_)) * x_sign;
        entity.y += (min_step_ + util::generate_uniform_real() * (max_step_ - min_step_)) * y_sign;
    }
}
}  // namespace mover