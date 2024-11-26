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
    zero, state << 1, 0;

    // Create the initial state vector which is |0>^n
    for (int i = 0; i < qubits.size() - 1; i++)
      state = Eigen::kroneckerProduct(state, zero).eval();

    // Evaluate gates
    for (const auto &gate : circ.getGates()) {
      state = gate->get_matrix(qubits.size()) * state;
      std::cout << gate->get_matrix(qubits.size()) << std::endl
                << std::endl;
    }
    return state;
  }

private:
};

#endif