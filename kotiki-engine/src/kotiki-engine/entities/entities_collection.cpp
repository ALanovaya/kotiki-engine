#include "kotiki-engine/entities/entities_collection.hpp"

#include <random>

namespace entity {
EntitiesCollection::EntitiesCollection(std::vector<Entity> const& entities)
    : entities_(entities), max_number_of_moving_entites_(entities.size()) {
    SampleNewIndices();
}

EntitiesCollection::EntitiesCollection(std::vector<Entity> const& entities,
                                       std::size_t max_number_of_moving_entites)
    : entities_(entities),
      max_number_of_moving_entites_(std::min(entities.size(), max_number_of_moving_entites)) {
    SampleNewIndices();
}

void EntitiesCollection::SampleNewIndices() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, entities_.size() - 1);

    moving_entities_indices_.clear();
    for (int i = 0; i < max_number_of_moving_entites_; ++i) {
        moving_entities_indices_.insert(distr(rd));
    }
}
}  // namespace entity