#ifndef GATE_HPP
#define GATE_HPP

#include <Eigen/Dense>
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
  }

  /**
   * @brief Gives the string representation of the gate.
   *
   * @return The string representation of the gate.
   */
  virtual std::string to_string() const = 0;

  /**
   * @brief Returns the number of qubits the gate acts on.
   *
   * @return The number of qubits the gate acts on.
   */
  int num_qubits() const { return qubits.size(); }

private:
  // Disallow copy and assignment
  Gate(const Gate &) = delete;
  Gate &operator=(const Gate &) = delete;

protected:
  std::vector<int> qubits;
  std::vector<int> controls;
};

#endif // GATE_HPP