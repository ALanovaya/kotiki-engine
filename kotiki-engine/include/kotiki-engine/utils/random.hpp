#include <random>

double sample_uniform() {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    static std::uniform_real_distribution distr(0.0, 1.0);

    return distr(eng);
}