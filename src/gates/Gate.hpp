#ifndef GATE_HPP
#define GATE_HPP

#include <Eigen/Dense>
#include <unsupported/Eigen/KroneckerProduct>
#include <vector>

/**
 * @class Gate
 * @brief A class representing a quantum gate, inheriting from Eigen::MatrixXcd.
 *
 * The Gate class extends Eigen's `MatrixXcd` class to represent complex-valued
 * square matrices.
 * This class initializes a matrix with a specified dimension and sets all
 * elements to zero by default.
 */
class Gate : public Eigen::MatrixXcd {
public:
  /**
   * @brief Virtual destructor for the Gate class.
   */
  virtual ~Gate() = default;

  /**
   * @brief Constructs a Gate with a specified dimension.
   *
   * Initializes a square matrix of complex numbers with the specified dimension
   * and sets all elements to zero.
   *
   * @param dim The dimension of the square matrix (number of rows and columns).
   */
  Gate(int dim, std::vector<int> qubits, std::vector<int> controls = {})
      : Eigen::MatrixXcd() {
    this->resize(dim, dim);
    this->setZero();
    this->qubits = qubits;
    this->controls = controls;

    // Projection operators
    P0x0 << 1, 0, 0, 0;
    P1x1 << 0, 0, 0, 1;
  }

  /**
   * @brief Gives the string representation of the gate.
   *
   * @return The string representation of the gate.
   */

  /**
   * @brief Returns the number of qubits the gate acts on.
   *
   * @return The number of qubits the gate acts on.
   */
  int num_qubits() const { return qubits.size(); }

  // TODO: Implement multi control gate support
  /**
   * @brief Generates the unitary matrix for the gate.
   *
   * @param n The total number of qubits in the system.
   * @return The resulting operator matrix as an Eigen::MatrixXcd.
   */
  Eigen::MatrixXcd get_matrix(int n) {
    Eigen::MatrixXcd op = Eigen::MatrixXcd::Identity(1, 1);
    Eigen::MatrixXcd op2 = Eigen::MatrixXcd::Identity(1, 1);
    if (qubits.size() > 1) {
      for (int i = 0; i < n; ++i) {
        if (i == qubits[0]) {
          op = Eigen::kroneckerProduct(op, P0x0).eval();
          op2 = Eigen::kroneckerProduct(op2, P1x1).eval();
        } else if (i == qubits[1]) {
          op = Eigen::kroneckerProduct(op, I).eval();
          op2 = Eigen::kroneckerProduct(op2, *this).eval();
        } else {
          op = Eigen::kroneckerProduct(op, I).eval();
          op2 = Eigen::kroneckerProduct(op2, I).eval();
        }
      }
      op += op2;
    } else {
      for (int i = 0; i < n; ++i) {
        if (i == qubits[0]) {
          op = Eigen::kroneckerProduct(op, *this).eval();
        } else {
          op = Eigen::kroneckerProduct(I, op).eval();
        }
      }
    }

    return op;
  }

private:
  // Projection operators
  Eigen::MatrixXcd P0x0 = Eigen::MatrixXcd(2, 2);
  Eigen::MatrixXcd P1x1 = Eigen::MatrixXcd(2, 2);
  Eigen::MatrixXcd I = Eigen::MatrixXcd::Identity(2, 2);

protected:
  std::vector<int> qubits;
  std::vector<int> controls;
};

#endif // GATE_HPP