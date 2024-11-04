#ifndef PAULIX_HPP
#define PAULIX_HPP

#include "gate.hpp"
#include <Eigen/Dense>

/**
 * @class PauliX
 * @brief A class representing the Pauli-X gate.
 *
 * The Pauli-X gate is a single-qubit gate that is equivalent to the classical
 * NOT gate. It flips the state of a qubit from |0⟩ to |1⟩ and vice versa.
 */
class PauliX : public Gate {
public:
  /**
   * @brief Constructs a Pauli-X gate.
   *
   * Initializes a 2x2 matrix representing the Pauli-X gate.
   */
  PauliX() : Gate(2) {
    this->operator()(0, 1) = 1;
    this->operator()(1, 0) = 1;
  }
};

#endif // PAULIX_HPP