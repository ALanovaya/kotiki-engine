#pragma once

#include <kotiki-engine/core/movers/mover.hpp>

namespace mover {
class RandomMover : public Mover {
private:
    double min_step_;
    double max_step_;

public:
    RandomMover(double min_step = 0, double max_step = 1);
    void Move(std::vector<entity::Entity> &entities);
};
}  // namespace mover