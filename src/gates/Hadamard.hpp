#ifndef H_HPP
#define H_HPP

#include "Gate.hpp"
#include <Eigen/Dense>
#include <vector>

class H : public Gate {
public:
  /**
   * @brief Constructs a Hadamard gate with specified target and control qubits.
   *
   * Initializes a 2x2 matrix representing the Hadamard gate with the specified
   * target and control qubits.
   *
   * @param qubits The target and control qubits.
   * @param controls The control qubits.
   */
  H(std::vector<int> qubits, std::vector<int> controls = {})
      : Gate(2, qubits, controls) {
    (*this)(0, 0) = 1;
    (*this)(0, 1) = 1;
    (*this)(1, 0) = 1;
    (*this)(1, 1) = -1;
    (*this) *= 1 / std::sqrt(2);
  }

  std::string to_string() const { return "H"; }
};

#endif
