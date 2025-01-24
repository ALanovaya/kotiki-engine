#pragma once

#include <random>

namespace util {

// Template base class of random generator
template <typename T>
class RandomGenerator {
protected:
    std::random_device rd_;
    std::mt19937 gen_;

    T min_;
    T max_;

public:
    RandomGenerator(T min, T max) : rd_(), gen_(rd_()), min_(min), max_(max) {};

    /**
     * Generates random number in range [this->min_, this->max_]
     */
    virtual T Generate() = 0;
    virtual void SetMin(T min) = 0;
    virtual void SetMax(T min) = 0;
    virtual void SetMinMax(T min, T max) = 0;
};

// Template base class of random real generator
template <typename T>
class RandomRealGenerator : public RandomGenerator<T> {
private:
    std::uniform_real_distribution<T> distr_;

public:
    RandomRealGenerator(T min, T max) : RandomGenerator<T>(min, max), distr_(min, max) {}

    /**
     * Generates random real number in range [this->min_, this->max_]
     */
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

    void SetMinMax(T min, T max) override final {
        this->min_ = min;
        this->max_ = max;
        this->distr_ = std::uniform_real_distribution<T>(this->min_, this->max_);
    };
};

// Template base class of random integer generator
template <typename T>
class RandomIntGenerator : public RandomGenerator<T> {
private:
    std::uniform_int_distribution<T> distr_;

public:
    RandomIntGenerator(T min, T max) : RandomGenerator<T>(min, max), distr_(min, max) {}

    /**
     * Generates random integer number in range [this->min_, this->max_]
     */
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

    void SetMinMax(T min, T max) override final {
        this->min_ = min;
        this->max_ = max;
        this->distr_ = std::uniform_int_distribution<T>(this->min_, this->max_);
    };
};

/**
 * Generates real number in range [0, 1]
 */
double generate_uniform_real();
}  // namespace util