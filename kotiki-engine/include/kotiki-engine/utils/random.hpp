#pragma once

#include <random>

namespace util {

template <typename T>
class RandomGenerator {
protected:
    std::random_device rd_;
    std::mt19937 gen_;

public:
    RandomGenerator() : rd_(), gen_(rd_()) {};
    virtual T Sample() = 0;
};

template <typename T>
class RandomRealGenerator : public RandomGenerator<T> {
private:
    std::uniform_real_distribution<T> distr_;

public:
    RandomRealGenerator(T min, T max) : RandomGenerator<T>(), distr_(min, max) {}

    T Sample() override final {
        return distr_(this->gen_);
    }
};

template <typename T>
class RandomIntGenerator : public RandomGenerator<T> {
private:
    std::uniform_int_distribution<T> distr_;

public:
    RandomIntGenerator(T min, T max) : RandomGenerator<T>(), distr_(min, max) {}

    T Sample() override final {
        return distr_(this->gen_);
    }
};

double sample_uniform_real();
}  // namespace util