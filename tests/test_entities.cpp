#include <gtest/gtest.h>

#include "kotiki-engine/entities/scene_manager.hpp"

namespace {
int number_of_entities = 4;
entity::FieldParams field_params = {-1000, -1000, 2000, 2000};

TEST(SceneManager, NoMoving) {
    std::vector<entity::Entity> entities(number_of_entities, {1.0, 1.0});
    entity::SceneManager entities_collection_1(entities, field_params, 0);
    entity::SceneManager entities_collection_2(entities, field_params, 4);
    entities_collection_2.SetMaxMoving(0);

    EXPECT_EQ(entities_collection_1.GetMaxMoving(), 0);
    EXPECT_TRUE(entities_collection_1.GetIndices().empty());

    EXPECT_EQ(entities_collection_2.GetMaxMoving(), 0);
    EXPECT_TRUE(entities_collection_2.GetIndices().empty());
}

TEST(SceneManager, StartCoordinates) {
    std::vector<entity::Entity> entities(number_of_entities, {1.0, 1.0});
    entity::SceneManager entities_collection(entities, field_params, number_of_entities);

    EXPECT_EQ(entities_collection.GetStartCoordinates().size(), entities.size());
    for (int i = 0; i < entities.size(); ++i) {
        EXPECT_EQ(entities_collection.GetStartCoordinates()[i].first, entities[i].x);
        EXPECT_EQ(entities_collection.GetStartCoordinates()[i].second, entities[i].y);
    }
}

}  // namespace