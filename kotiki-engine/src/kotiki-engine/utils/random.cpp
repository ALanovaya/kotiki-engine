#include "kotiki-engine/utils/random.hpp"

namespace util {
double sample_uniform_real() {
    static RandomRealGenerator<double> gen(0.0, 1.0);

    return gen.Sample();
}
}  // namespace util