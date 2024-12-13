#ifndef OPERATION_HPP
#define OPERATION_HPP

#include "../gates/Gate.hpp"
#include "Eigen/Dense"
#include <memory>
#include <vector>

/**
 * @class Operation
 * @brief Representing a prebuilt operation, a set of gates applied on the
 * specified qubits.
 *
 */
class Operation {
public:
  /**
   * @brief Costructor for the Operation class
   *
   * @param qi The qubit indices the operation will be applied the ordering can
   * be relevant in some cases.
   *
   */
  Operation(std::vector<int> qi) { qubitIndices_ = qi; }
  virtual ~Operation() {}
  std::vector<std::shared_ptr<Gate>> Gates;

private:
  std::vector<int> qubitIndices_;
};
#endif