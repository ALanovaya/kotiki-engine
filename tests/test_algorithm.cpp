#include <gtest/gtest.h>

#include "kotiki-engine/core/algorithms/algorithms.hpp"
#include "kotiki-engine/core/metrics/metrics.hpp"
#include "kotiki-engine/entities/scene_manager.hpp"
#include "kotiki-engine/entities/states.hpp"

namespace {
FieldParams field_params = {-1000, -1000, 2000, 2000};

TEST(TestNaive, FightingOnR0Test) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{1.0, 1.0}, {1.0, 1.9}, {3.0, 4.0}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Fighting);
    ASSERT_EQ(states[1], entity::EntityState::Fighting);
    ASSERT_NE(states[2], entity::EntityState::Fighting);
}

TEST(TestNaive, AllFightingTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{1.0, 1.0}, {1.3, 1.3}, {1.5, 1.5}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Fighting);
    ASSERT_EQ(states[1], entity::EntityState::Fighting);
    ASSERT_EQ(states[2], entity::EntityState::Fighting);
}

TEST(TestNaive, NoFightingTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{1.0, 1.0}, {3.0, 3.0}, {5.0, 5.0}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_NE(states[0], entity::EntityState::Fighting);
    ASSERT_NE(states[1], entity::EntityState::Fighting);
    ASSERT_NE(states[2], entity::EntityState::Fighting);
}

TEST(TestNaive, AllCalmTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{10.0, 10.0}, {30.0, 30.0}, {50.0, 50.0}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Calm);
    ASSERT_EQ(states[1], entity::EntityState::Calm);
    ASSERT_EQ(states[2], entity::EntityState::Calm);
}

TEST(TestNaive, SingleEntityTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::NaiveAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{69.0, 420.0}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 1);
    ASSERT_EQ(states[0], entity::EntityState::Calm);
}

TEST(TestGridLookup, FightingOnR0Test) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::GridLookupAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{1.0, 1.0}, {1.0, 1.9}, {3.0, 4.0}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Fighting);
    ASSERT_EQ(states[1], entity::EntityState::Fighting);
    ASSERT_NE(states[2], entity::EntityState::Fighting);
}

TEST(TestGridLookup, AllFightingTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::GridLookupAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{1.0, 1.0}, {1.3, 1.3}, {1.5, 1.5}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Fighting);
    ASSERT_EQ(states[1], entity::EntityState::Fighting);
    ASSERT_EQ(states[2], entity::EntityState::Fighting);
}

TEST(TestGridLookup, NoFightingTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::GridLookupAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{1.0, 1.0}, {3.0, 3.0}, {5.0, 5.0}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_NE(states[0], entity::EntityState::Fighting);
    ASSERT_NE(states[1], entity::EntityState::Fighting);
    ASSERT_NE(states[2], entity::EntityState::Fighting);
}

TEST(TestGridLookup, AllCalmTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::GridLookupAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{10.0, 10.0}, {30.0, 30.0}, {50.0, 50.0}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 3);
    ASSERT_EQ(states[0], entity::EntityState::Calm);
    ASSERT_EQ(states[1], entity::EntityState::Calm);
    ASSERT_EQ(states[2], entity::EntityState::Calm);
}

TEST(TestGridLookup, SingleEntityTest) {
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::GridLookupAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{69.0, 420.0}}, field_params);
    auto states = algo.GetStates(kotiki);
    ASSERT_EQ(states.size(), 1);
    ASSERT_EQ(states[0], entity::EntityState::Calm);
}

TEST(TestGridLookup, BorderEntitesTest) {
    FieldParams field_params = {0, 0, 2000, 2000};
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::GridLookupAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki({{0.0, 0.0}, {2000.0, 2000.0}}, field_params);
    EXPECT_NO_THROW(algo.GetStates(kotiki));
}

TEST(TestGridLookup, OutOfBorderEntitesTest) {
    FieldParams field_params = {0, 0, 1000, 1000};
    auto R0 = 1;
    auto R1 = 10;
    auto algo = algo::GridLookupAlgorithm(R0, R1, std::make_unique<algo::EuclideanMetric>());
    entity::SceneManager kotiki1({{10.0, 10.0}, {2000.0, 2000.0}}, field_params);
    entity::SceneManager kotiki2({{-1.0, -1.0}, {500.0, 500.0}}, field_params);
    EXPECT_THROW(algo.GetStates(kotiki1), std::invalid_argument);
    EXPECT_THROW(algo.GetStates(kotiki2), std::invalid_argument);
}
}  // namespace
