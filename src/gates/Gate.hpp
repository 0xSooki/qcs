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
  virtual std::string to_string() const = 0; // Pure virtual function

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
   * @param qubits The target and control qubits.
   * @param controls The control qubits, defaults to an empty vector.
   */
  Gate(int dim, const std::vector<int> &qubits,
       const std::vector<int> &controls = {})
      : Eigen::MatrixXcd(dim, dim), qubits(qubits), controls(controls) {
    this->setZero();
    P0x0 << 1, 0, 0, 0;
    P1x1 << 0, 0, 0, 1;
  }

  /**
   * @brief Returns the qubits the gate acts on.
   *
   * @return The vector of target qubits.
   */
  const std::vector<int> &get_qubits() const { return qubits; }

  /**
   * @brief Returns the control qubits for the gate.
   *
   * @return The vector of control qubits.
   */
  const std::vector<int> &get_controls() const { return controls; }

  /**
   * @brief Returns the number of qubits the gate acts on.
   *
   * @return The number of target qubits.
   */
  int num_qubits() const { return qubits.size(); }

  /**
   * @brief Generates the unitary matrix for the gate, supporting multi-control
   * gates.
   *
   * @param n The total number of qubits in the system.
   * @return The resulting operator matrix as an Eigen::MatrixXcd.
   */
  Eigen::MatrixXcd get_matrix(int n) {
    Eigen::MatrixXcd op = Eigen::MatrixXcd::Identity(1, 1);
    Eigen::MatrixXcd op2 = Eigen::MatrixXcd::Identity(1, 1);

    if (!controls.empty()) { // Multi-control gate logic
      for (int i = 0; i < n; ++i) {
        if (std::find(controls.begin(), controls.end(), i) != controls.end()) {
          op = Eigen::kroneckerProduct(op, P0x0).eval();
          op2 = Eigen::kroneckerProduct(op2, P1x1).eval();
        } else if (std::find(qubits.begin(), qubits.end(), i) != qubits.end()) {
          op = Eigen::kroneckerProduct(op, I).eval();
          op2 = Eigen::kroneckerProduct(op2, *this).eval();
        } else {
          op = Eigen::kroneckerProduct(op, I).eval();
          op2 = Eigen::kroneckerProduct(op2, I).eval();
        }
      }
      op += op2;
    } else { // Regular gates
      for (int i = 0; i < n; ++i) {
        if (std::find(qubits.begin(), qubits.end(), i) != qubits.end()) {
          op = Eigen::kroneckerProduct(op, *this).eval();
        } else {
          op = Eigen::kroneckerProduct(op, I).eval();
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
  std::vector<int> qubits;   // Target qubits for the gate
  std::vector<int> controls; // Control qubits for the gate
};

#endif // GATE_HPP
