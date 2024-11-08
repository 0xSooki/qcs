#ifndef ROTATIONGATE_HPP
#define ROTATIONGATE_HPP

#include "gate.hpp"
#include <Eigen/Dense>
#include <cmath>
#include <complex>
#include <string>
#include <vector>

enum Axis {
  X = 0,
  Y = 1,
  Z = 2,
};

std::complex<double> roundWithPrecision(std::complex<double> c) {
  double n = 4.0;
  std::complex<double> result(
      std::round(c.real() * pow(10.0, n)) / pow(10.0, n),
      std::round(c.imag() * pow(10.0, n)) / pow(10.0, n));
  return result;
}
/**
 * @class RotationGate
 * @brief A class representing a quantum rotation gate around a set axis by an
 * arbitrary angle, inheriting from the Gate class.
 *
 * The RotationGate class is a gate with dimensions of 2×2
 * This class initializes the matrix representation of the rotationgate based on
 * its axis and angle teta
 */
class RotationGate : public Gate {
public:
  /**
   * @brief Destructor for the RotationGate class.
   */
  ~RotationGate(){};

  /**
   * @brief Constructs a RotationGate representing rotation around a given axis,
   * with a given teta angle. Sets the elements of the complex 2×2 matrix.
   *
   * @param axis The axis of the rotation operation. One of x, y, z.
   * @param teta The angle of the rotation in radians (has a period of 4*pi)
   */

  RotationGate(Axis axis, double teta, std::vector<int> qubits,
               std::vector<int> controls = {})
      : Gate(2, qubits, controls) {
    teta_ = teta;
    std::complex<double> i(0.0, 1.0);
    std::complex<double> teta_comp(teta / 2, 0.0);
    switch (axis) {
    case Z:
      (*this)(0, 0) = roundWithPrecision(std::exp(-1.0 * i * teta_comp));
      (*this)(1, 1) = roundWithPrecision(std::exp(i * teta_comp));
      axis_ = "Z";
      break;
    case X:
      (*this)(0, 0) = roundWithPrecision(std::cos(teta_comp));
      (*this)(0, 1) = roundWithPrecision(i * -1.0 * std::sin(teta_comp));
      (*this)(1, 0) = roundWithPrecision(i * -1.0 * std::sin(teta_comp));
      (*this)(1, 1) = roundWithPrecision(std::cos(teta_comp));
      axis_ = "X";
      break;
    case Y:
      (*this)(0, 0) = roundWithPrecision(std::cos(teta_comp));
      (*this)(0, 1) = roundWithPrecision(-1.0 * std::sin(teta_comp));
      (*this)(1, 0) = roundWithPrecision(std::sin(teta_comp));
      (*this)(1, 1) = roundWithPrecision(std::cos(teta_comp));
      axis_ = "Y";
      break;
    default:
      axis_ = "reee";
      throw std::invalid_argument("Invalid axis");
    }
  }
  /**
   * @brief Gives the string representation of the gate.
   *
   * @return The string representation of the gate, in format
   * "R"+"axis"+"(angle)".
   */
  std::string to_string() const {
    std::string r = "R" + this->axis_ + "(" + std::to_string(teta_) + ")";
    return r;
  }

private:
  std::string axis_;
  double teta_;
};

#endif // ROTATIONGATE_HPP