#include "Random.hh"

namespace MP {
	
// Specific template instantiations
std::vector<int> GetRandomValues(const size_t size, const int intervalMin, const int intervalMax);
std::vector<double> GetRandomValues(const size_t size, const double intervalMin, const double intervalMax);

}