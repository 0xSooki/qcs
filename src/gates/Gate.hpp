#ifndef GATE_HPP
#define GATE_HPP

#include <Eigen/Dense>

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
  Gate(int dim) : Eigen::MatrixXcd() {
    this->resize(dim, dim);
    this->setZero();
  }
};

#endif // GATE_HPP