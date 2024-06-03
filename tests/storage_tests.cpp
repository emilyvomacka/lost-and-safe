#include <catch2/catch_test_macros.hpp>

bool returnTrue() { return true; }

TEST_CASE("testing catch2 Framework") {
  REQUIRE(returnTrue() == true);
}