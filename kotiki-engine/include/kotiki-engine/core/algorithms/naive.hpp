#include <kotiki-engine/core/algorithms/algorithm.hpp>

namespace algo {
class NaiveAlgorithm : public Algorithm {
public:
    NaiveAlgorithm(double R0, double R1, Metric* metric) : Algorithm(R0, R1, metric) {};
    std::vector<entity::EntityState> GetStates(std::vector<entity::Entity>& entities);
};
}  // namespace algo