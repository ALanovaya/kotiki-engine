#pragma once

#include <stdexcept>

#include "kotiki-engine/core/movers/mover.hpp"
#include "kotiki-engine/utils/random.hpp"

namespace mover {
class RandomMover : public Mover {
private:
    coord_t min_step_;
    coord_t max_step_;

    util::RandomRealGenerator<coord_t> gen_;

    void MoveInternal(entity::EntitiesCollection& entities);

public:
    RandomMover(coord_t min_step, coord_t max_step);

    void SetMinStep(coord_t min_step) {
        if (max_step_ < min_step) {
            throw std::invalid_argument(
                    "In Random Mover minimal step must be less or equal to maximal step");
        }
        min_step_ = min_step;
    }

    void SetMaxStep(coord_t max_step) {
        if (max_step < min_step_) {
            throw std::invalid_argument(
                    "In Random Mover minimal step must be less or equal to maximal step");
        }
        max_step_ = max_step;
    }

    int GetMinStep() {
        return min_step_;
    }

    int GetMaxStep() {
        return max_step_;
    }
};
}  // namespace mover