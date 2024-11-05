#include <iostream> 
#include "QuantumCircuit.hpp"
#include "file_io.hpp"

// Constructor intitilizes the circuit with a special number of qubits
QuantumCircuit::QuantumCircuit(int numQubits):numQubits(numQubits), stateVector(numQubits){}

// Method add qubit to the circuit
void QuantumCircuit::addQubits(){
    ++numQubits;
    stateVector.expand(numQubits); // increase the state vector to fit the new qubit
}

// Apply a single qubit gate to a specific qubit
// TODO

// Apply a two qubit gate to control and target qubits
//TODO

//Retrieves the current state vector
//TODO

//Write the circuit to a file
void QuantumCircuit::writeToFile(const std::string& filename){
    writeCircuitToFile(*this, filename);
}

// Read the circuit to a file
void QuantumCircuit::readFromFile(const std::string& filename){
    readCircuitToFile(*this, filename);
}