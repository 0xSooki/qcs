#include <gtest/gtest.h>
#include "../src/io/File-io.hpp"
#include <nlohmann/json.hpp> 
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json; 

TEST(FileIOTest, WriteCircuitToFile) {
    // Create a quantum circuit
    QuantumCircuit circuit({0, 1});
    circuit.addGate(std::make_shared<PauliX>(std::vector<int>{0}));

    // JSON file name
    std::string filename = "test_circuit.json";
    ASSERT_NO_THROW(writeCircuitToFile(circuit, filename));
    ASSERT_TRUE(fs::exists(filename)) << "File was not created.";

    // Read file and check content
    try {
        std::ifstream file(filename);
        ASSERT_TRUE(file.is_open()) << "Failed to open file for reading.";

        json parsed;
        ASSERT_NO_THROW(parsed = json::parse(file)) << "Failed to parse JSON file.";

        // Validate the contents of the JSON
        ASSERT_EQ(parsed["numQubits"], 2) << "Number of qubits does not match.";
        ASSERT_EQ(parsed["gates"].size(), 1) << "Gate count does not match.";
        ASSERT_EQ(parsed["gates"][0]["gate"], "X") << "Gate type does not match.";
        ASSERT_EQ(parsed["gates"][0]["qubits"][0], 0) << "Qubit index does not match.";

        file.close();
    } catch (...) {
        fs::remove(filename); 
        throw;
    }

    // Remove the file after the test
    fs::remove(filename);
}
