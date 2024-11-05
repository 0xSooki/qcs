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
        void applyGate(const Gate& gate, int qubitIndex); // Apply a single-qubit gate
        void applyGate(const Gate& gate, int controlQubit, int targetQubit); // Apply two qubits gate with control and target

        // Get the current state vector
        Eigen::VectorXcd getCurrentState() const;

        // read-write I/O methos
        void writeToFile(const std::string& filename);
        void readFromFile(const std::string& filenam);

    private:
        int numQubits; 
        StateVector stateVector; // manage the state of the ciruit's qubits
        std::vector<std::pair<Gate, std::pair<int, int>>> gates; // stor gates qubits indices

}


#endif //QUANTUMCIRCUIT_HPP