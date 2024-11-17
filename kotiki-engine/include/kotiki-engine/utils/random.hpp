#pragma once

#include <random>

namespace util {

template <typename T>
class RandomGenerator {
protected:
    std::random_device rd_;
    std::mt19937 gen_;

    T min_;
    T max_;

public:
    RandomGenerator(T min, T max) : rd_(), gen_(rd_()), min_(min), max_(max) {};
    virtual T Generate() = 0;
    virtual void SetMin(T min) = 0;
    virtual void SetMax(T min) = 0;
};

template <typename T>
class RandomRealGenerator : public RandomGenerator<T> {
private:
    std::uniform_real_distribution<T> distr_;

public:
    RandomRealGenerator(T min, T max) : RandomGenerator<T>(min, max), distr_(min, max) {}

    T Generate() override final {
        return distr_(this->gen_);
    }

    void SetMin(T min) override final {
        this->min_ = min;
        this->distr_ = std::uniform_real_distribution<T>(this->min_, this->max_);
    };

    void SetMax(T max) override final {
        this->max_ = max;
        this->distr_ = std::uniform_real_distribution<T>(this->min_, this->max_);
    };
};

template <typename T>
class RandomIntGenerator : public RandomGenerator<T> {
private:
    std::uniform_int_distribution<T> distr_;

public:
    RandomIntGenerator(T min, T max) : RandomGenerator<T>(min, max), distr_(min, max) {}

    T Generate() override final {
        return distr_(this->gen_);
    }

    void SetMin(T min) override final {
        this->min_ = min;
        this->distr_ = std::uniform_int_distribution<T>(this->min_, this->max_);
    };

    void SetMax(T max) override final {
        this->max_ = max;
        this->distr_ = std::uniform_int_distribution<T>(this->min_, this->max_);
    };
};

double generate_uniform_real();
}  // namespace util