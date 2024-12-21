#include <gtest/gtest.h>

#include "absl/base/log_severity.h"
#include "absl/base/macros.h"
#include "absl/flags/parse.h"
#include "absl/log/globals.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

using namespace std;

int main(int argc, char *argv[]) 
{
  int rc{};
  
  absl::SetStderrThreshold(absl::LogSeverityAtLeast::kInfo);
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  //? if (!absl::log_internal::IsInitialized()) absl::InitializeLog();
  
  
  // First, pass arguments to Gtest
  // it will catch args such as --gtest_filter=Log_test.Base
  ::testing::InitGoogleTest(&argc, argv);
  rc = RUN_ALL_TESTS();
  return rc;
}



