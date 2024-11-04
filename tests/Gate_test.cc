#include "../src/gates/Gate.hpp"
#include <gtest/gtest.h>

TEST(Gate, BasicAssertions) {
  Gate gate(2);
  EXPECT_EQ(gate.rows(), 2);
  EXPECT_EQ(gate.cols(), 2);
  EXPECT_EQ(gate.size(), 4);
  EXPECT_EQ(gate(0, 0), 0.0);
  EXPECT_EQ(gate(0, 1), 0.0);
  EXPECT_EQ(gate(1, 0), 0.0);
  EXPECT_EQ(gate(1, 1), 0.0);
}