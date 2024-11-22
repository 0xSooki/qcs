#ifndef CNOT_HPP
#define CNOT_HPP

#include "Gate.hpp"
#include <Eigen/Dense>
#include <vector>

class CNOT : public Gate {
public:
  CNOT(std::vector<int> qubits, std::vector<int> controls)
      : Gate(2, qubits, controls) {
    (*this)(0, 0) = 0;
    (*this)(0, 1) = 1;
    (*this)(1, 0) = 1;
    (*this)(1, 1) = 0;
  }

  std::string to_string() const { return "CNOT"; }
};

#endif