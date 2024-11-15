#include <cmath>
#include <kotiki-engine/core/trajectory/trajectory.hpp>

#include <gtest/gtest.h>

namespace {
TEST(TestTrajectory, LinearTrajectoryTest) {
    trajectory::Trajectory linear_trajectory("t", "2 * t", "t");

    std::pair<double, double> start_coordinates_0 = {0.0, 0.0};
    auto pos_at_0 = linear_trajectory.GetPosition(start_coordinates_0, 0);
    EXPECT_EQ(pos_at_0.first, 0.0);
    EXPECT_EQ(pos_at_0.second, 0.0);

    std::pair<double, double> start_coordinates_1 = {1.0, 1.0};
    auto pos_at_1 = linear_trajectory.GetPosition(start_coordinates_1, 1);
    EXPECT_EQ(pos_at_1.first, 2.0);
    EXPECT_EQ(pos_at_1.second, 3.0);

    std::pair<double, double> start_coordinates_2 = {-1.0, -2.0};
    auto pos_at_2 = linear_trajectory.GetPosition(start_coordinates_2, 2);
    EXPECT_EQ(pos_at_2.first, 1.0);
    EXPECT_EQ(pos_at_2.second, 2.0);
}

TEST(TestTrajectory, CircleTrajectoryTest) {
    trajectory::Trajectory circle_trajectory("cos(t)", "sin(t)", "t");

    std::pair<double, double> start_coordinates_0 = {0.0, 0.0};
    auto pos_at_0 = circle_trajectory.GetPosition(start_coordinates_0, 0);
    EXPECT_EQ(pos_at_0.first, 1.0);
    EXPECT_EQ(pos_at_0.second, 0.0);

    std::pair<double, double> start_coordinates_1 = {1.0, 1.0};
    auto pos_at_pi = circle_trajectory.GetPosition(start_coordinates_1, M_PI);
    EXPECT_NEAR(pos_at_pi.first, 0.0, 1e-6);
    EXPECT_NEAR(pos_at_pi.second, 1.0, 1e-6);
}

TEST(TestTrajectory, ParabolaTrajectoryTest) {
    trajectory::Trajectory parabola_trajectory("t", "t*t", "t");

    std::pair<double, double> start_coordinates_0 = {0.0, 0.0};
    auto pos_at_0 = parabola_trajectory.GetPosition(start_coordinates_0, 0);
    EXPECT_EQ(pos_at_0.first, 0.0);
    EXPECT_EQ(pos_at_0.second, 0.0);

    std::pair<double, double> start_coordinates_1 = {2.0, 3.0};
    auto pos_at_1 = parabola_trajectory.GetPosition(start_coordinates_1, 1);
    EXPECT_EQ(pos_at_1.first, 3.0);
    EXPECT_EQ(pos_at_1.second, 4.0);

    std::pair<double, double> start_coordinates_2 = {-1.0, -1.0};
    auto pos_at_2 = parabola_trajectory.GetPosition(start_coordinates_2, 2);
    EXPECT_EQ(pos_at_2.first, 1.0);
    EXPECT_EQ(pos_at_2.second, 3.0);
}

TEST(TestTrajectory, SineWaveTrajectoryTest) {
    trajectory::Trajectory sine_wave_trajectory("t", "sin(t)", "t");

    std::pair<double, double> start_coordinates_0 = {0.0, 0.0};
    auto pos_at_0 = sine_wave_trajectory.GetPosition(start_coordinates_0, 0);
    EXPECT_EQ(pos_at_0.first, 0.0);
    EXPECT_EQ(pos_at_0.second, 0.0);

    std::pair<double, double> start_coordinates_1 = {1.0, -1.0};
    auto pos_at_pi_2 = sine_wave_trajectory.GetPosition(start_coordinates_1, M_PI / 2);
    EXPECT_NEAR(pos_at_pi_2.first, M_PI / 2 + 1, 1e-6);
    EXPECT_NEAR(pos_at_pi_2.second, 0, 1e-6);

    std::pair<double, double> start_coordinates_2 = {-2.0, 2.0};
    auto pos_at_pi = sine_wave_trajectory.GetPosition(start_coordinates_2, M_PI);
    EXPECT_NEAR(pos_at_pi.first, M_PI - 2, 1e-6);
    EXPECT_NEAR(pos_at_pi.second, 2, 1e-6);
}

TEST(TestTrajectory, InvalidVariableInX) {
    EXPECT_THROW(
            trajectory::Trajectory traj("x + t", "2 * t", "t"),
    std::invalid_argument
    );
}
TEST(TestTrajectory, InvalidVariableInT) {
    EXPECT_THROW(
            trajectory::Trajectory traj("x + t", "2 * t", "x"),
    std::invalid_argument
    );
}

TEST(TestTrajectory, InvalidVariableInY) {
    EXPECT_THROW(
            trajectory::Trajectory traj("t", "y + 2 * t", "t"),
    std::invalid_argument
    );
}

TEST(TestTrajectory, InvalidVariablesInBothExpressions) {
    EXPECT_THROW(
            trajectory::Trajectory traj("x + t", "y + t", "t"),
    std::invalid_argument
    );
}

TEST(TestTrajectory, InvalidVariableDifferentFromTimeVariable) {
    EXPECT_THROW(
            trajectory::Trajectory traj("a + b", "b * c", "t"),
    std::invalid_argument
    );
}

TEST(TestTrajectory, ValidTrajectoryWithOnlyVariableT) {
    EXPECT_NO_THROW(
            trajectory::Trajectory traj("t", "2 * t", "t")
    );
}

TEST(TestTrajectory, ValidTrajectoryWithOnlyVariableX) {
    EXPECT_NO_THROW(
            trajectory::Trajectory traj("sin(x) * cos(x)", "0", "x")
    );
}

}  // namespace
