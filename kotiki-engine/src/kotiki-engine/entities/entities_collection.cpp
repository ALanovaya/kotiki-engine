#include "kotiki-engine/entities/entities_collection.hpp"

#include <random>

namespace entity {
EntitiesCollection::EntitiesCollection(std::vector<Entity> const& entities)
    : entities_(entities),
      number_of_moving_entites_(entities.size()),
      moving_entities_indices_(entities.size()) {
    for (int i = 0; i < entities.size(); ++i) {
        moving_entities_indices_[i] = i;
    }
}

EntitiesCollection::EntitiesCollection(std::vector<Entity> const& entities,
                                       int number_of_moving_entites)
    : entities_(entities),
      number_of_moving_entites_(number_of_moving_entites),
      moving_entities_indices_(entities.size()) {
    SampleNewIndices();
}

void EntitiesCollection::SampleNewIndices() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distr(0, entities_.size() - 1);

    for (auto& index : moving_entities_indices_) {
        index = distr(rd);
    }
}
}  // namespace entity