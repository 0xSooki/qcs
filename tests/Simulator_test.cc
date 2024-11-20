#include "../src/controller/QuantumCircuit.hpp"
#include "../src/controller/Simulator.hpp"
#include "../src/gates/CNOT.hpp"
#include "../src/gates/Hadamard.hpp"
#include "../src/gates/PauliGates.hpp"
#include <gtest/gtest.h>

TEST(QuantumCircuitTest, AddPauliXGate) {
  QuantumCircuit circ(1);
  circ.addGate(std::make_shared<PauliX>(PauliX(std::vector<int>{0})));

  Simulator sim;
  Eigen::VectorXcd result = sim.run(circ);

  Eigen::VectorXcd expected(2);
  expected << 0, 1;
  ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

TEST(QuantumCircuitTest, AddHadamardGate) {
  QuantumCircuit circ(1);
  circ.addGate(std::make_shared<H>(H(std::vector<int>{0})));

  Simulator sim;
  Eigen::VectorXcd result = sim.run(circ);

  Eigen::VectorXcd expected(2);
  expected << 1 / sqrt(2), 1 / sqrt(2);
  ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

TEST(QuantumCircuitTest, AddCNOTGate) {
  QuantumCircuit circ(2);
  circ.addGate(std::make_shared<PauliX>(PauliX(std::vector<int>{0})));
  circ.addGate(std::make_shared<CNOT>(
      CNOT(std::vector<int>{0, 1}, std::vector<int>{0})));

  Simulator sim;
  Eigen::VectorXcd result = sim.run(circ);

  Eigen::VectorXcd expected(4);
  expected << 0, 0, 0, 1;
  ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

TEST(QuantumCircuitTest, CombinedGates) {
  QuantumCircuit circ(3);
  circ.addGate(std::make_shared<PauliX>(PauliX(std::vector<int>{0})));
  circ.addGate(std::make_shared<H>(H(std::vector<int>{0})));
  circ.addGate(std::make_shared<CNOT>(
      CNOT(std::vector<int>{0, 2}, std::vector<int>{0})));

  Simulator sim;
  Eigen::VectorXcd result = sim.run(circ);

  Eigen::VectorXcd expected(8);
  expected << 1 / sqrt(2), 0, 0, 0, 0, -1 / sqrt(2), 0, 0;
  ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

TEST(SimulatorTest, EmptyCircuit) {
  QuantumCircuit circ(1);
  Simulator sim;
  Eigen::VectorXcd result = sim.run(circ);

  Eigen::VectorXcd expected(2);
  expected << 1, 0;
  ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

TEST(SimulatorTest, ThreeQubitIdentity) {
  QuantumCircuit circ(3);
  Simulator sim;
  Eigen::VectorXcd result = sim.run(circ);

  Eigen::VectorXcd expected(8);
  expected << 1, 0, 0, 0, 0, 0, 0, 0;
  ASSERT_TRUE(result.isApprox(expected, 1e-6));
}
