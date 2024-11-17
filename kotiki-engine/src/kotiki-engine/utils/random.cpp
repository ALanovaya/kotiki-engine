#include "kotiki-engine/utils/random.hpp"

namespace util {
double generate_uniform_real() {
    static RandomRealGenerator<double> gen(0.0, 1.0);

    return gen.Generate();
}
}  // namespace util