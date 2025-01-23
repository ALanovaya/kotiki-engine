#pragma once

#include <stdexcept>

#include "kotiki-engine/core/movers/mover.hpp"
#include "kotiki-engine/utils/random.hpp"

namespace mover {

// Random mover class
// Moves entities randomly across scene
class RandomMover : public Mover {
private:
    coord_t min_step_;  // Minimal move of entity
    coord_t max_step_;  // Maximal move of entity

    util::RandomRealGenerator<coord_t> gen_;  // Random uniform real generator

    void MoveInternal(entity::SceneManager& scene);

public:
    /**
     * Random Mover constructor
     *
     * @param min_step Minimal move of entity
     * @param max_step Maximal move of entity
     */
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