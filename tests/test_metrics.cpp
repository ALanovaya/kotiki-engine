#include <gtest/gtest.h>
#include <stdexcept>
#include <kotiki-engine/entities/entity.hpp>
#include <kotiki-engine/core/metrics/minkowski.hpp>
#include <kotiki-engine/core/metrics/euclidean.hpp>
#include <kotiki-engine/core/metrics/manhattan.hpp>
#include <kotiki-engine/core/metrics/chebyshev.hpp>

namespace {
TEST(MinkowskiMetricTest, MinkowskiWithP2) {
    algo::MinkowskiMetric minkowski_metric(2.0);

    entity::Entity first;
    first.x = 1.0;
    first.y = 2.0;

    entity::Entity second;
    second.x = 4.0;
    second.y = 6.0;

    coord_t result = minkowski_metric.Calculate(first, second);
    coord_t expected = std::sqrt(std::pow(4.0 - 1.0, 2) + std::pow(6.0 - 2.0, 2));

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(MinkowskiMetricTest, MinkowskiWithP1) {
    algo::MinkowskiMetric minkowski_metric(1.0);

    entity::Entity first;
    first.x = 1.0;
    first.y = 2.0;

    entity::Entity second;
    second.x = 4.0;
    second.y = 6.0;

    coord_t result = minkowski_metric.Calculate(first, second);
    coord_t expected = std::abs(4.0 - 1.0) + std::abs(6.0 - 2.0);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(MinkowskiMetricTest, InvalidPZero) {
    EXPECT_THROW(algo::MinkowskiMetric minkowski_metric(0.0), std::invalid_argument);
}

TEST(MinkowskiMetricTest, InvalidPNegative) {
    EXPECT_THROW(algo::MinkowskiMetric minkowski_metric(-1.0), std::invalid_argument);
}

TEST(EuclideanMetricTest, EuclideanMetric) {
    algo::EuclideanMetric euclidean_metric;

    entity::Entity first;
    first.x = 1.0;
    first.y = 2.0;

    entity::Entity second;
    second.x = 4.0;
    second.y = 6.0;

    coord_t result = euclidean_metric.Calculate(first, second);
    coord_t expected = std::sqrt(std::pow(4.0 - 1.0, 2) + std::pow(6.0 - 2.0, 2));

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(ManhattanMetricTest, ManhattanMetric) {
    algo::ManhattanMetric manhattan_metric;

    entity::Entity first;
    first.x = 1.0;
    first.y = 2.0;

    entity::Entity second;
    second.x = 4.0;
    second.y = 6.0;

    coord_t result = manhattan_metric.Calculate(first, second);
    coord_t expected = std::abs(4.0 - 1.0) + std::abs(6.0 - 2.0);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(ChebyshevMetricTest, ChebyshevMetric) {
    algo::ChebyshevMetric chebyshev_metric;

    entity::Entity first;
    first.x = 1.0;
    first.y = 2.0;

    entity::Entity second;
    second.x = 4.0;
    second.y = 6.0;

    coord_t result = chebyshev_metric.Calculate(first, second);
    coord_t expected = std::max(std::abs(4.0 - 1.0), std::abs(6.0 - 2.0));

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(ChebyshevMetricTest, ChebyshevWithZeroDistance) {
    algo::ChebyshevMetric chebyshev_metric;

    entity::Entity first;
    first.x = 1.0;
    first.y = 2.0;

    entity::Entity second;
    second.x = 1.0;
    second.y = 2.0;

    coord_t result = chebyshev_metric.Calculate(first, second);
    coord_t expected = 0.0;

    EXPECT_DOUBLE_EQ(result, expected);
}
}  // namespace