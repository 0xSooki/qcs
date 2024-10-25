#include <Eigen/Dense>

/**
 * @class PauliX
 * @brief Represents the Pauli-X (NOT) gate, inheriting from Gate.
 *
 * The Pauli-X gate flips the state of a qubit (|0⟩ to |1⟩ and vice versa).
 */

class PauliX : public Eigen::MatrixXcd {
public:
  /**
   * @brief Constructor for the Pauli-X gate.
   */
  PauliX() : Eigen::MatrixXcd(2, 2) {
    (*this)(0, 0) = 0;
    (*this)(0, 1) = 1;
    (*this)(1, 0) = 1;
    (*this)(1, 1) = 0;
  }
};