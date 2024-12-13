#ifndef BELLSTATE_HPP
#define BELLSTATE_HPP

#include "../gates/CNOT.hpp"
#include "../gates/Hadamard.hpp"
#include "Eigen/Dense"
#include "Operation.hpp"
#include <memory>
#include <vector>

/**
 * @class BellState
 *
 * @brief Representing the creation of a Bell pair, a classical example of
 * entanglement.
 *
 * Contains a hadamard and a CNOT gate.
 *
 */
class BellState : public Operation {
public:
  /**
   * @brief Constructor creating a Bell state on the specified qubits
   *
   *@param qi The qubit indices to use in the Bell state.
   */
  BellState(std::vector<int> qi) : Operation(qi) {
    std::vector<int> first = std::vector<int>(qi[0]);
    H h0 = H(first);
    CNOT cn1 = CNOT(qi, first);
    Gates.push_back(std::make_shared<H>(h0));
    Gates.push_back(std::make_shared<CNOT>(cn1));
  }
  // Destructor
  ~BellState() {}
};
#endif