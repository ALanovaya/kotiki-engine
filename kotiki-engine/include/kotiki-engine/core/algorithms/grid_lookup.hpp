#include <kotiki-engine/core/algorithms/algorithm.hpp>

namespace algo {
class GridLookupAlgorithm : public Algorithm {
private:
    using Grid = std::vector<std::vector<std::vector<int>>>;

    int grid_size_;
    Grid grid_;

public:
    GridLookupAlgorithm(double R0, double R1, Metric* metric);

    std::vector<entity::EntityState> GetStates(std::vector<entity::Entity>& entities);
};
}  // namespace algo