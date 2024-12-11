#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Eigen/Dense"
#include "QuantumCircuit.hpp"
#include "unsupported/Eigen/KroneckerProduct"
#include <iostream>

/**
 * @class Simulator
 * @brief Representing a simulator object, would be a quantum computer in the
 * real world.
 *
 * A simulator object can be constructed with a quantum circuit as input,
 * and is able to evaluate the circuit with the given parameters such as noise
 * models etc.
 */
class Simulator {

public:
  /**
   * @brief Constructs a Simulator object.
   *
   */
  Simulator() {}

  /**
   * @brief Evaluates the quantum circuit and returns the final state in
   * little endian ordering meaning the least significant bit is the first
   * element eg. H|00> = |00> + |01> / sqrt(2)
   *
   * @return The final state of the quantum circuit in little endian ordering.
   * @param circ The quantum circuit to be simulated.
   */
  Eigen::VectorXcd run(QuantumCircuit circ) const {
    std::vector<int> qubits = circ.getQubits();
    Eigen::VectorXcd mult(qubits.size());
    mult.setOnes();

    // Initialize the state to |0>
    Eigen::VectorXcd state(2);
    Eigen::VectorXcd zero(2);
    Eigen::VectorXcd one(2);
    zero << 1, 0;
    one << 0, 1;

    if (qubits[0] == 1)
      state << one;
    else
      state << zero;

    // Create the initial state vector which is |0>^n
    for (int i = 1; i < qubits.size(); i++)
      if (qubits[i] == 1)
        state = Eigen::kroneckerProduct(state, one).eval();
      else
        state = Eigen::kroneckerProduct(state, zero).eval();
    std::cout << (state) << std::endl;
    // Evaluate gates
    for (const auto &gate : circ.getGates()) {
      state = gate->get_matrix(qubits.size()) * state;
      std::cout << gate->get_matrix(qubits.size()) << std::endl << std::endl;
    }
    return state;
  }

private:
};

#endif
