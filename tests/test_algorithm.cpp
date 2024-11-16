#include <gtest/gtest.h>

#include "kotiki-engine/core/algorithms/algorithms.hpp"
#include "kotiki-engine/core/metrics/metrics.hpp"
#include "kotiki-engine/entities/entities_collection.hpp"
#include "kotiki-engine/entities/states.hpp"

namespace {
TEST(TestNaive, FightingOnR0Test) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, new algo::EuclideanMetric);
    entity::EntitiesCollection kotiki({{1.0, 1.0}, {1.0, 1.9}, {3.0, 4.0}});
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Fighting);
    ASSERT_EQ(states[1], entity::EntityState::Fighting);
    ASSERT_NE(states[2], entity::EntityState::Fighting);
}

TEST(TestNaive, AllFightingTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, new algo::EuclideanMetric);
    entity::EntitiesCollection kotiki({{1.0, 1.0}, {1.3, 1.3}, {1.5, 1.5}});
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Fighting);
    ASSERT_EQ(states[1], entity::EntityState::Fighting);
    ASSERT_EQ(states[2], entity::EntityState::Fighting);
}

TEST(TestNaive, NoFightingTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, new algo::EuclideanMetric);
    entity::EntitiesCollection kotiki({{1.0, 1.0}, {3.0, 3.0}, {5.0, 5.0}});
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_NE(states[0], entity::EntityState::Fighting);
    ASSERT_NE(states[1], entity::EntityState::Fighting);
    ASSERT_NE(states[2], entity::EntityState::Fighting);
}

TEST(TestNaive, AllCalmTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, new algo::EuclideanMetric);
    entity::EntitiesCollection kotiki({{10.0, 10.0}, {30.0, 30.0}, {50.0, 50.0}});
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Calm);
    ASSERT_EQ(states[1], entity::EntityState::Calm);
    ASSERT_EQ(states[2], entity::EntityState::Calm);
}

TEST(TestNaive, SingleEntityTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, new algo::EuclideanMetric);
    entity::EntitiesCollection kotiki({{69.0, 420.0}});
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 1);
    ASSERT_EQ(states[0], entity::EntityState::Calm);
}
}  // namespace
