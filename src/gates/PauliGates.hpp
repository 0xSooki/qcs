#ifndef PAULIGATES_HPP
#define PAULIGATES_HPP

#include "RotationGate.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

/**
 * @class PauliX
 * @brief A class representing a quantum rotation gate around the X axis axis by
 * an angle of pi inheriting from the RotationGate class
 * 
 * Matrix form:
 * (0,0) (1,0)
 * (1,0) (0,0)
 */
class PauliX : public RotationGate {
public:
  /**
   * @brief Constructs a PauliX gate, by calling the parent constructor with the
   * set parameters.
   * 
   * @param qubits The target and control qubits.
   * @param controls The control qubits, defaults to an empty vector.
   */
  PauliX(std::vector<int> qubits, std::vector<int> controls = {})
      : RotationGate(X, -M_PI, qubits, controls) {
    std::complex<double> i_minus(0.0, -1.0);
    (*this) << (i_minus * (*this));
  };
  /**
   * @brief Gives the string representation of the gate.
   *
   * @return The string representation of the gate, in format
   * "X".
   */
  std::string to_string() const { return "X"; }
  /**
   * @brief Destructor for the PauliX class.
   */
  ~PauliX(){};
};
/**
 * @class PauliY
 * @brief A class representing a quantum rotation gate around the Y axis axis by
 * an angle of pi inheriting from the RotationGate class
 * 
 * Matrix form:
 * (0,0) (0,-1)
 * (0,1)  (0,0)
 */
class PauliY : public RotationGate {
public:
  /**
   * @brief Constructs a PauliY gate, by calling the parent constructor with the
   * set parameters.
   * 
   * @param qubits The target and control qubits.
   * @param controls The control qubits, defaults to an empty vector.
   */
  PauliY(std::vector<int> qubits, std::vector<int> controls = {})
      : RotationGate(Y, -M_PI, qubits, controls) {
    std::complex<double> i_minus(0.0, -1.0);
    (*this) << (i_minus * (*this));
  };
  /**
   * @brief Gives the string representation of the gate.
   *
   * @return The string representation of the gate, in format
   * "Y".
   */
  std::string to_string() const { return "Y"; }
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
   * 
   * @param qubits The target and control qubits.
   * @param controls The control qubits, defaults to an empty vector.
   */
  PauliZ(std::vector<int> qubits, std::vector<int> controls = {})
      : RotationGate(Z, -M_PI, qubits, controls) {
    std::complex<double> i_minus(0.0, -1.0);
    (*this) << (i_minus * (*this));
  };
  /**
   * @brief Gives the string representation of the gate.
   *
   * @return The string representation of the gate, in format
   * "Z".
   */
  std::string to_string() const { return "Z"; }
  /**
   * @brief Destructor for the PauliZ class.
   */
  ~PauliZ(){};
};
#endif
