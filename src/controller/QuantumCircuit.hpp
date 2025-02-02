#ifndef QUANTUMCIRCUIT_HPP
#define QUANTUMCIRCUIT_HPP

#include "../gates/Gate.hpp"
#include "../gates/PauliGates.hpp"
#include "../gates/RotationGate.hpp"
#include "../gates/CNOT.hpp"
#include "../gates/Hadamard.hpp"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @class QuantumCircuit
 * @brief A class representing a quantum circuit with a set of quantum gates.
 * 
 * The QuantumCircuit class holds a collection of gates that operate on qubits.
 * A quantum circuit can be constructed by specifying the number of qubits with specific states and
 * then adding gates to the circuit.
 * 
 * The quantum circuit supports operations like adding gates to the circuit
 * and retrieving the list of gates in the circuit.
 */
class QuantumCircuit {
public:
    /**
     * @brief Constructs a QuantumCircuit with qubits with their initial states.
     * 
     * @param qubits The vector of qubits in the circuit with their initial states.
     */
    QuantumCircuit(const std::vector<int>& qubits) : qubits_(qubits) {}

    /**
     * @brief Default constructor for a new Quantum Circuit object
     * 
     */
    QuantumCircuit() : qubits_({}) {}
    
    /**
     * @brief Adds a gate to the quantum circuit.
     * 
     * @param gate A shared pointer to the gate to be added to the circuit.
     */
    void addGate(const std::shared_ptr<Gate>& gate) {
        gates_.push_back(gate);
    }

    /**
     * @brief Returns the list of gates in the quantum circuit.
     * 
     * @return A const reference to the vector of gates.
     */
    const std::vector<std::shared_ptr<Gate>>& getGates() const {
        return gates_;
    }

    /**
     * @brief Returns the vector of qubits in the quantum circuit.
     * 
     * @return The vector of qubits.
     */
    const std::vector<int>& getQubits() const {
        return qubits_;
    }

    /**
     * @brief Adds a new qubit to the circuit.
     * @param qubit The qubit state to be added.
     */
    void addQubit(int qubit) {
        qubits_.push_back(qubit);
    }
    
private:
    std::vector<int> qubits_;
    std::vector<std::shared_ptr<Gate>> gates_;
};

#endif // QUANTUMCIRCUIT_HPP
