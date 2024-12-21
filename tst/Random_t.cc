
#include "Random.hh"
// Std includes
// Google Test
#include <gtest/gtest.h>
#include <absl/log/log.h>

using namespace std;
using namespace MP;

namespace {
 vector<double> dvec;
}

TEST(Random, Base)
{
	size_t size = 1000;
	dvec = GetRandomValues(size, 0.0, 1.0);

	LOG(INFO) << "We have " << dvec.size() << " random values in vec";
	
	// We should have size number of elements in vec
	ASSERT_TRUE(dvec.size()==size);
	
	// The first and last elements must differ
	EXPECT_TRUE(dvec.at(0) != dvec.at(size-1));
	
}


TEST(Random, Sort)
{
  //TODO: Sorting
  // a) Sort dvec in ascending order, use standard library sort functions, use at least two sort methods
  // b) Test that dvec is really sorted
  // c) Use Google Benchmark library to measure performance of the each sort method
  EXPECT_TRUE(true);
}



TEST(Random, Search)
{
  //TODO: Search dvec for specific values 0.0, 0.5 and the median value of the sorted array
  // a) Use unsorted array first for searches
  // b) Then use the sorted array for the searches
  // c) Use at least two different search method, preferably from standard library
  // d) Use Google Benchmark library to measure performance of the each search method
  EXPECT_TRUE(true);
}