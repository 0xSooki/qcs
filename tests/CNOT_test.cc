#include "../src/gates/CNOT.hpp"
#include "Eigen/src/Core/Matrix.h"
#include <gtest/gtest.h>

TEST(CNOT, get_matrix) {
  CNOT cnot({0, 1}, {0});
  Eigen::MatrixXcd mtx(4, 4);
  mtx << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0;
  EXPECT_EQ(cnot.num_qubits(), 2);
  EXPECT_EQ(cnot.to_string(), "CNOT");
  EXPECT_EQ(cnot.get_matrix(2), mtx);
}