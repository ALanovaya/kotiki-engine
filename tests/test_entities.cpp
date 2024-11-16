#include <gtest/gtest.h>

#include "kotiki-engine/entities/entities_collection.hpp"

namespace {
TEST(EntitiesCollection, AllMoving) {
    int max_moving_number = 4;
    std::vector<entity::Entity> entities(max_moving_number, {1.0, 1.0});
    entity::EntitiesCollection entities_colllection_1(entities);
    entity::EntitiesCollection entities_colllection_2(entities, 4);
    entity::EntitiesCollection entities_colllection_3(entities, max_moving_number * 10);
    entity::EntitiesCollection entities_colllection_4(entities, 1);
    entities_colllection_4.SetMaxMoving(max_moving_number);

    EXPECT_EQ(entities_colllection_1.GetMaxMoving(), max_moving_number);
    EXPECT_EQ(entities_colllection_2.GetMaxMoving(), max_moving_number);
    EXPECT_EQ(entities_colllection_3.GetMaxMoving(), max_moving_number);
    EXPECT_EQ(entities_colllection_4.GetMaxMoving(), max_moving_number);
}

TEST(EntitiesCollection, NoMoving) {
    int number_of_entities = 4;
    std::vector<entity::Entity> entities(number_of_entities, {1.0, 1.0});
    entity::EntitiesCollection entities_colllection_1(entities, 0);
    entity::EntitiesCollection entities_colllection_2(entities, 4);
    entities_colllection_2.SetMaxMoving(0);

    EXPECT_EQ(entities_colllection_1.GetMaxMoving(), 0);
    EXPECT_TRUE(entities_colllection_1.GetIndices().empty());

    EXPECT_EQ(entities_colllection_2.GetMaxMoving(), 0);
    EXPECT_TRUE(entities_colllection_2.GetIndices().empty());
}
}  // namespace