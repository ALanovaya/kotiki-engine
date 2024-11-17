#include <gtest/gtest.h>

#include "kotiki-engine/entities/entities_collection.hpp"

namespace {
int number_of_entities = 4;
FieldParams field_params = {-1000, -1000, 2000, 2000};

TEST(EntitiesCollection, AllMoving) {
    std::vector<entity::Entity> entities(number_of_entities, {1.0, 1.0});
    entity::EntitiesCollection entities_collection_1(entities, field_params);
    entity::EntitiesCollection entities_collection_2(entities, 4, field_params);
    entity::EntitiesCollection entities_collection_3(entities, number_of_entities * 10,
                                                     field_params);
    entity::EntitiesCollection entities_collection_4(entities, 1, field_params);
    entities_collection_4.SetMaxMoving(number_of_entities);

    EXPECT_EQ(entities_collection_1.GetMaxMoving(), number_of_entities);
    EXPECT_EQ(entities_collection_2.GetMaxMoving(), number_of_entities);
    EXPECT_EQ(entities_collection_3.GetMaxMoving(), number_of_entities);
    EXPECT_EQ(entities_collection_4.GetMaxMoving(), number_of_entities);
}

TEST(EntitiesCollection, NoMoving) {
    std::vector<entity::Entity> entities(number_of_entities, {1.0, 1.0});
    entity::EntitiesCollection entities_collection_1(entities, 0, field_params);
    entity::EntitiesCollection entities_collection_2(entities, 4, field_params);
    entities_collection_2.SetMaxMoving(0);

    EXPECT_EQ(entities_collection_1.GetMaxMoving(), 0);
    EXPECT_TRUE(entities_collection_1.GetIndices().empty());

    EXPECT_EQ(entities_collection_2.GetMaxMoving(), 0);
    EXPECT_TRUE(entities_collection_2.GetIndices().empty());
}

TEST(EntitiesCollection, StartCoordinates) {
    std::vector<entity::Entity> entities(number_of_entities, {1.0, 1.0});
    entity::EntitiesCollection entities_collection(entities, number_of_entities, field_params);

    EXPECT_EQ(entities_collection.GetStartCoordinates().size(), entities.size());
    for (int i = 0; i < entities.size(); ++i) {
        EXPECT_EQ(entities_collection.GetStartCoordinates()[i].first, entities[i].x);
        EXPECT_EQ(entities_collection.GetStartCoordinates()[i].second, entities[i].y);
    }
}

}  // namespace