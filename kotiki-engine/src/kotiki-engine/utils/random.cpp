#include "kotiki-engine/utils/random.hpp"

#include <random>

double sample_uniform_real() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution distr(0.0, 1.0);

    return distr(gen);
}