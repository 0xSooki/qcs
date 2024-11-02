#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <string>
#include <QuantumCircuit.h> 
/**
 * Write a quantumn circuit into a file
 * @param circuit QuantumCircuit object to write
 * @param filename to store circuit data.
 */

/**
 * Write a quantumn circuit into a file
 * @param filename containing circuit data
 * @return QuantumCircuit object is recreated from the file
 */

void writeCircuitToFile(const QuantumCircuit& circuit, const std::string& filename);
QuantumCircuit readCircuitToFile(const std::string& filename);

#endif // FILE_IO_HPP