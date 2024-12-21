#include <vector>
#include <cassert>
#include "absl/random/random.h"

namespace MP {
	
template <typename T> 
std::vector<T> GetRandomValues(const size_t size, const T intervalMin, const T intervalMax)
{
	assert(size > 0);        // Must be greater than zero
	std::vector<T> vec;  
	vec.reserve(size);   // Reserve a space for the future values
	absl::BitGen bitgen_;
	for(int i=0; i<size; i++) {
		T elem = absl::Uniform(bitgen_, intervalMin, intervalMax);
		vec.push_back(elem);
	}
	
	return vec;
}

} // namespace