#ifndef PAULIGATES_HPP
#define PAULIGATES_HPP

#include "RotationGate.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

/**
 * @class PauliX
 * @brief A class representing a quantum rotation gate around the X axis axis by
 * an angle of pi inheriting from the RotationGate class
 */
class PauliX : public RotationGate {
public:
  /**
   * @brief Constructs a PauliX gate, by calling the parent constructor with the
   * set parameters.
   * Matrix form:
   * (0,0) (1,0)
   * (1,0) (0,0)
   */
  PauliX() : RotationGate(X, -M_PI) {
    std::complex<double> i_minus(0.0, -1.0);
    (*this) << (i_minus * (*this));
  };
  /**
   * @brief Destructor for the PauliX class.
   */
  ~PauliX(){};
};
/**
 * @class PauliY
 * @brief A class representing a quantum rotation gate around the Y axis axis by
 * an angle of pi inheriting from the RotationGate class
 */
class PauliY : public RotationGate {
public:
  /**
   * @brief Constructs a PauliY gate, by calling the parent constructor with the
   * set parameters.
   *Matrix form :
   * (0,0) (0,-1)
   * (0,1)  (0,0)
   */
  PauliY() : RotationGate(Y, -M_PI) {
    std::complex<double> i_minus(0.0, -1.0);
    (*this) << (i_minus * (*this));
  };
  /**
   * @brief Destructor for the PauliY class.
   */
  ~PauliY(){};
};
/**
 * @class PauliZ
 * @brief A class representing a quantum rotation gate around the Z axis axis by
 * an angle of pi inheriting from the RotationGate class
 * Matrix form:
 * (1,0)   (0,0)
 * (0,0) (-1,-0)
 */
class PauliZ : public RotationGate {
public:
  /**
   * @brief Constructs a PauliZ gate, by calling the parent constructor with the
   * set parameters.
   */
  PauliZ() : RotationGate(Z, -M_PI) {
    std::complex<double> i_minus(0.0, -1.0);
    (*this) << (i_minus * (*this));
  };
  /**
   * @brief Destructor for the PauliZ class.
   */
  ~PauliZ(){};
};
#endif