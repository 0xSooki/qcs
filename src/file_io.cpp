#include <file_io.hpp>
#include <fstream>
#include <iostream>

/**
 * writeCircuitToFile
 * The file is stored in a readable text format.
 */

/**
 * readCircuitToFile
 * Make sure that the file matches the format.
 */

void writeCircuitToFile(const QuantumCircuit& circuit, const std::string& filename) {
    std::ofstream circuitFile(filename);
    if(circuitFile.is_open()){
        // Need to implement later for writing circuit components to file (JSON)
        // TODO
        circuitFile.close();
    }else{
        std::cerr<<"Cannot open file for writing\n";
    }
}

QuantumCircuit readCircuitToFile(const std::string& filename){
    std::ifstream circuitFile(filename);
    if(circuitFile.is_open()){
        // Need to implement later for reading data from circuitFile and instantiate QuantumCircuit object
        // TODO
        circuitFile.close();
    }else{
        std::cerr<<"Cannot open file for reading\n";
    }
}