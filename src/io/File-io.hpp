#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "../controller/QuantumCircuit.hpp"

using json = nlohmann::json;

/**
 * @brief Writes a quantum circuit to a JSON file.
 */
void writeCircuitToFile(const QuantumCircuit& circuit, const std::string& filename) {
    json j;

    // Add number of qubits to JSON
    j["numQubits"] = circuit.getQubits().size();

    // Store the gates
    for (const auto& gate : circuit.getGates()) {
        json gateJson;

        // Determine gate type and add it to JSON
        if (dynamic_cast<const PauliX*>(gate.get())) {
            gateJson["gate"] = "X";
        } else if (dynamic_cast<const PauliY*>(gate.get())) {
            gateJson["gate"] = "Y";
        } else if (dynamic_cast<const PauliZ*>(gate.get())) {
            gateJson["gate"] = "Z";
        } else if (dynamic_cast<const H*>(gate.get())) {
            gateJson["gate"] = "H";
        } else if (dynamic_cast<const CNOT*>(gate.get())) {
            gateJson["gate"] = "CNOT";
        }

        gateJson["qubits"] = gate->get_qubits();
        if (!gate->get_controls().empty()) {
            gateJson["controls"] = gate->get_controls();
        }

        j["gates"].push_back(gateJson);
    }

    // Write JSON to file
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Could not open file for writing.");
    }
    file << j.dump(4);
}

/**
 * @brief Reads a quantum circuit from a JSON file.
 */
void readCircuitFromFile(QuantumCircuit& circuit, const std::string& filename) {
    std::ifstream file(filename);
    json j;
    file >> j;

    for (int i = 0; i < j["numQubits"]; ++i) {
        circuit.addQubit(i);
    }

    for (const auto& gateJson : j["gates"]) {
        std::string gateType = gateJson["gate"];
        std::vector<int> qubits = gateJson["qubits"].get<std::vector<int>>();
        std::vector<int> controls = gateJson.contains("controls") ? gateJson["controls"].get<std::vector<int>>() : std::vector<int>();

        if (gateType == "X") {
            circuit.addGate(std::make_shared<PauliX>(qubits, controls));
        } else if (gateType == "Y") {
            circuit.addGate(std::make_shared<PauliY>(qubits, controls));
        } else if (gateType == "Z") {
            circuit.addGate(std::make_shared<PauliZ>(qubits, controls));
        } else if (gateType == "H") {
            circuit.addGate(std::make_shared<H>(qubits, controls));
        }
    }
}

#endif // FILE_IO_HPP
