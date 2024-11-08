#include "../src/gates/PauliGates.hpp"
#include "Eigen/src/Core/Matrix.h"
#include <complex>
#include <gtest/gtest.h>

TEST(PauliX, PauliXBasicAssertions) {
  PauliX x({0});
  Eigen::MatrixXcd mtx(2, 2);
  mtx << 0, 1, 1, 0;
  EXPECT_EQ(x.num_qubits(), 1);
  EXPECT_EQ(x.to_string(), "X");
  EXPECT_EQ(x, mtx);
}

TEST(PauliY, PauliYBasicAssertions) {
  PauliY y({0});
  Eigen::MatrixXcd mtx(2, 2);
  mtx << 0, -std::complex<double>(0, 1), std::complex<double>(0, 1), 0;
  EXPECT_EQ(y.num_qubits(), 1);
  EXPECT_EQ(y.to_string(), "Y");
  EXPECT_EQ(y, mtx);
}

TEST(PauliZ, PauliZBasicAssertions) {
  PauliZ z({0});
  Eigen::MatrixXcd mtx(2, 2);
  mtx << 1, 0, 0, -1;
  EXPECT_EQ(z.num_qubits(), 1);
  EXPECT_EQ(z.to_string(), "Z");
  EXPECT_EQ(z, mtx);
}