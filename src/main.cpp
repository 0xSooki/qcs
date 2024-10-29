#include "gates/PauliX.hpp"
#include <Eigen/Dense>
#include <iostream>

int main() {
  Eigen::VectorXcd q(2);
  q << 1, 0;

  std::cout << "|0> = " << std::endl << q << std::endl;

  PauliX x;
  Eigen::MatrixXcd result = x * q;

  std::cout << "X|0> = " << std::endl << result << std::endl;
  return 0;
}