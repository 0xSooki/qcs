#ifndef QUANTUMCIRCUIT_HPP
#define QUANTUMCIRCUIT_HPP

#include <vector>
#include <string>
#include <Eigen/Dense> // The library for matrix and vector 
#include "Gate.hpp" 
#include "StateVector.hpp"

class QuantumCircuit{
    public:
        QuantumCircuit(int numQubits); //constructor

        // Methods to add Qubits and apply Gates
        void addQubits(); // add qubits to the circuit
        
        // Apply applyGate function for single-qubit and two qubit with control and target
        void applyGate(const Gate& gate, const std::vector<int>& qubitIndices)

        // Get the current state vector
        Eigen::VectorXcd getCurrentState() const;

        // read-write I/O methos
        void writeToFile(const std::string& filename);
        void readFromFile(const std::string& filenam);

    private:
        int numQubits; 
        StateVector stateVector; // manage the state of the ciruit's qubits
        std::vector<std::pair<Gate, std::pair<int, int>>> gates; // store gate and qubits indices
};

#endif //QUANTUMCIRCUIT_HPP