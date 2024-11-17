#pragma once

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
    RandomMover(coord_t min_step = 0.0, coord_t max_step = 1.0);
};
}  // namespace mover