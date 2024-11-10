#include <iostream>
#include "QuantumCircuit.hpp"
#include "file_io.hpp"

// Constructor initializes the circuit with a special number of qubits
QuantumCircuit::QuantumCircuit(int numQubits) : numQubits(numQubits), stateVector(numQubits) {}

// Method add qubit to the circuit
void QuantumCircuit::addQubit()
{
    ++numQubits;
    stateVector.expand(numQubits); // Expand the state vector for new qubit
}

// Apply single and two qubit gate
void QuantumCircuit::applyGate(const Gate &gate, const std::vector<int> &qubitIndices)
{
    // Store the gate and it qubit
    gates.push_back({gate, qubitIndices});
    // Call applyGate function for handling single and two qubit in stateVector
    stateVector.applyGate(gate, qubitIndices);
}

// Retrieve the current state vector of the circuit
Eigen::VectorXcd QuantumCircuit::getCurrentState() const
{
    return stateVector.getState();
}
// Calculate the probabilities of each state based on the current state vector
std::vector<double> QuantumCircuit::computeProbabilities() const
{
    return stateVector.computeProbabilities(); // Need to update this method inside stateVector
}

// Write the circuit to a file
void QuantumCircuit::writeToFile(const std::string &filename)
{
    writeCircuitToFile(*this, filename);
}

// Read the circuit to a file
void QuantumCircuit::readFromFile(const std::string &filename)
{
    readCircuitToFile(*this, filename);
}