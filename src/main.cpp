#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>

#include "../libs/tinyfiledialogs/tinyfiledialogs.hpp"

#include "io/File-io.hpp"

#include "view/Button.hpp"
#include "view/PlaceholderGate.hpp"
#include "view/Result.hpp"
#include "view/VisualCNOT.hpp"
#include "view/VisualGate.hpp"
#include "view/VisualQubit.hpp"

#include "controller/QuantumCircuit.hpp"
#include "controller/Simulator.hpp"

#include "gates/Gate.hpp"
#include "gates/Hadamard.hpp"
#include "gates/PauliGates.hpp"
#include "gates/RotationGate.hpp"

int windowHeight = 800;
int windowWidth = 1400;
bool gateSelected = false;
char const *fileFilterPatterns[1] = {"*.json"};
std::vector<std::shared_ptr<Gate>> gates;
sf::Font font;
std::vector<VisualQubit> qubits;
bool cnotControl = false;
std::vector<VisualQubit>::iterator controlQubit;

int main() {
  std::filesystem::path fontPath = "../../resources/Roboto-Bold.ttf";

  if (!font.loadFromFile(fontPath)) {
    std::cout << "File path " << fontPath << " at absolute location "
              << absolute(fontPath) << " does not exist\n";
  }

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                          "Quantum Circuit Simulator", sf::Style::Close);

  VisualGate pauliX(sf::Vector2f(65, 65), "X", font);
  VisualGate pauliY(sf::Vector2f(65, 185), "Y", font);
  VisualGate pauliZ(sf::Vector2f(65, 305), "Z", font);
  VisualGate hadamard(sf::Vector2f(65, 425), "H", font);
  VisualGate cnot(sf::Vector2f(65, 545), "CNOT", font);

  sf::RectangleShape line(sf::Vector2f(windowHeight, 5));
  line.setFillColor(sf::Color::Black);
  line.setPosition(sf::Vector2f(140, 0));
  line.rotate(90.f);

  Button addQubitButton(sf::Vector2f(260, 250), "Add Qubit", font);
  Button removeQubitButton(sf::Vector2f(400, 250), "Remove Qubit", font, false);
  Button importButton(sf::Vector2f(windowWidth - 20, 20) - sf::Vector2f(190, 0),
                      "Import from file", font);
  Button exportButton(sf::Vector2f(windowWidth - 20, 20) - sf::Vector2f(360, 0),
                      "Export to file", font);
  Button evaluateButton(sf::Vector2f(160, 20), "Evaluate circuit", font);
  Button clearButton(sf::Vector2f(360, 20), "Clear circuit", font);

  Simulator simulator;
  Result result;

  qubits.push_back(VisualQubit(sf::Vector2f(260, 140), font, 0));

  auto unselectGates = [&]() {
    pauliX.setSelected(false);
    pauliY.setSelected(false);
    pauliZ.setSelected(false);
    hadamard.setSelected(false);
    cnot.setSelected(false);
    gateSelected = false;
  };

  auto toCircuit = [&]() {
    std::vector<int> initialStates;
    for (auto qubit = qubits.begin(); qubit != qubits.end(); qubit++) {
      initialStates.push_back(qubit->getInitialState());
    }

    QuantumCircuit circuit(initialStates);
    for (auto gate : gates) {
      circuit.addGate(gate);
    }

    return circuit;
  };

  auto clearCircuit = [&]() {
    gates.clear();
    for (auto qubit = qubits.begin(); qubit != qubits.end();) {
      if (qubit != qubits.begin()) {
        qubit->resetQubit();
        qubit = qubits.erase(qubit);
      } else {
        qubit->resetQubit();
        qubit++;
      }
    }

    unselectGates();

    addQubitButton.moveTo(sf::Vector2f(260, 250));
    removeQubitButton.moveTo(sf::Vector2f(400, 250));
    removeQubitButton.setVisible(false);
    result = Result();
  };

  auto addQubit = [&](int state) {
    qubits.push_back(
        VisualQubit(addQubitButton.getPosition(), font, qubits.size(), state));
    addQubitButton.moveTo(addQubitButton.getPosition() + sf::Vector2f(0, 110));
    removeQubitButton.moveTo(removeQubitButton.getPosition() +
                             sf::Vector2f(0, 110));
    removeQubitButton.setVisible(true);
  };

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          if (pauliX.isPressed(event.mouseButton.x, event.mouseButton.y)) {
            pauliX.setSelected(!pauliX.getSelected());
            pauliY.setSelected(false);
            pauliZ.setSelected(false);
            hadamard.setSelected(false);
            cnot.setSelected(false);

            cnotControl = false;
            gateSelected = pauliX.getSelected();
          }
          if (pauliY.isPressed(event.mouseButton.x, event.mouseButton.y)) {
            pauliX.setSelected(false);
            pauliY.setSelected(!pauliY.getSelected());
            pauliZ.setSelected(false);
            hadamard.setSelected(false);
            cnot.setSelected(false);

            cnotControl = false;
            gateSelected = pauliY.getSelected();
          }
          if (pauliZ.isPressed(event.mouseButton.x, event.mouseButton.y)) {
            pauliX.setSelected(false);
            pauliY.setSelected(false);
            pauliZ.setSelected(!pauliZ.getSelected());
            hadamard.setSelected(false);
            cnot.setSelected(false);

            cnotControl = false;
            gateSelected = pauliZ.getSelected();
          }
          if (hadamard.isPressed(event.mouseButton.x, event.mouseButton.y)) {
            pauliX.setSelected(false);
            pauliY.setSelected(false);
            pauliZ.setSelected(false);
            hadamard.setSelected(!hadamard.getSelected());
            cnot.setSelected(false);

            cnotControl = false;
            gateSelected = hadamard.getSelected();
          }
          if (cnot.isPressed(event.mouseButton.x, event.mouseButton.y) &&
              qubits.size() > 1) {
            pauliX.setSelected(false);
            pauliY.setSelected(false);
            pauliZ.setSelected(false);
            hadamard.setSelected(false);
            cnot.setSelected(!cnot.getSelected());

            gateSelected = cnot.getSelected();
          }
          for (auto qubit = qubits.begin(); qubit != qubits.end(); qubit++) {
            if (qubit->isPlaceholderClicked(event.mouseButton.x,
                                            event.mouseButton.y) &&
                gateSelected) {
              if (pauliX.getSelected()) {
                auto x =
                    std::make_shared<PauliX>(std::vector<int>{qubit->getID()});
                qubit->addGate("X", font, x);
                gates.push_back(x);
              } else if (pauliY.getSelected()) {
                auto y =
                    std::make_shared<PauliY>(std::vector<int>{qubit->getID()});
                qubit->addGate("Y", font, y);
                gates.push_back(y);
              } else if (pauliZ.getSelected()) {
                auto z =
                    std::make_shared<PauliZ>(std::vector<int>{qubit->getID()});
                qubit->addGate("Z", font, z);
                gates.push_back(z);
              } else if (hadamard.getSelected()) {
                auto h = std::make_shared<H>(std::vector<int>{qubit->getID()});
                qubit->addGate("H", font, h);
                gates.push_back(h);
              } else if (cnot.getSelected()) {
                if (cnotControl) {
                  auto cnot = std::make_shared<CNOT>(
                      std::vector<int>{qubit->getID(), controlQubit->getID()});
                  gates.push_back(cnot);

                  qubit->addCNOTGate(*controlQubit, cnot);

                  cnotControl = false;
                } else {
                  controlQubit = qubit;
                  cnotControl = true;
                }
              }

              if (!cnotControl) {
                unselectGates();
              }
            }
            if (qubit->isInitialStageClicked(event.mouseButton.x,
                                             event.mouseButton.y)) {
              qubit->switchInitialState();
            }
          }
          if (importButton.isPressed(event.mouseButton.x,
                                     event.mouseButton.y)) {
            char const *filename = tinyfd_openFileDialog(
                "Import a circuit from", // title
                NULL,                    // optional initial directory
                0,                       // number of filter patterns
                NULL, // char const * lFilterPatterns[2] = { "*.txt", "*.jpg" };
                NULL, // optional filter description
                0     // forbids multiple selections
            );

            if (filename != NULL) {
              QuantumCircuit circuit;
              readCircuitFromFile(circuit, filename);

              clearCircuit();

              qubits.pop_back();
              addQubitButton.moveTo(addQubitButton.getPosition() -
                                    sf::Vector2f(0, 110));
              removeQubitButton.moveTo(removeQubitButton.getPosition() -
                                       sf::Vector2f(0, 110));

              for (int initialState : circuit.getQubits()) {
                addQubit(initialState);
              }

              gates = circuit.getGates();

              for (auto gate : gates) {
                if (dynamic_cast<const PauliX *>(gate.get())) {
                  qubits[gate->get_qubits().at(0)].addGate("X", font, gate);
                } else if (dynamic_cast<const PauliY *>(gate.get())) {
                  qubits[gate->get_qubits().at(0)].addGate("Y", font, gate);
                } else if (dynamic_cast<const PauliZ *>(gate.get())) {
                  qubits[gate->get_qubits().at(0)].addGate("Z", font, gate);
                } else if (dynamic_cast<const H *>(gate.get())) {
                  qubits[gate->get_qubits().at(0)].addGate("H", font, gate);
                } else if (dynamic_cast<const CNOT *>(gate.get())) {
                  qubits[gate->get_qubits().at(0)].addCNOTGate(
                      qubits[gate->get_qubits().at(1)],
                      std::dynamic_pointer_cast<CNOT>(gate));
                }
              }
            }
          }
          if (exportButton.isPressed(event.mouseButton.x,
                                     event.mouseButton.y)) {
            char const *filename = tinyfd_saveFileDialog(
                "Save circuit to",  // title
                NULL,               // optional initial directory
                1,                  // number of filter patterns
                fileFilterPatterns, // char const * lFilterPatterns[2] = {
                                    // "*.txt", "*.jpg" };
                NULL                // forbids multiple selections
            );

            if (filename != NULL) {
              QuantumCircuit circuit = toCircuit();
              writeCircuitToFile(circuit, filename);
            }
          }
          if (addQubitButton.isPressed(event.mouseButton.x,
                                       event.mouseButton.y) &&
              qubits.size() < 4) {
            addQubit(0);
          }
          if (removeQubitButton.isPressed(event.mouseButton.x,
                                          event.mouseButton.y) &&
              removeQubitButton.isVisible()) {
            int id = qubits.back().getID();
            for (auto gate = gates.begin(); gate != gates.end();) {
              if ((*gate)->get_qubits().at(0) == id ||
                  (dynamic_cast<const CNOT *>((*gate).get()) &&
                   (*gate)->get_qubits().at(1) == id)) {
                gate = gates.erase(gate);
              } else {
                gate++;
              }
            }

            unselectGates();
            qubits.pop_back();
            addQubitButton.moveTo(addQubitButton.getPosition() -
                                  sf::Vector2f(0, 110));
            removeQubitButton.moveTo(removeQubitButton.getPosition() -
                                     sf::Vector2f(0, 110));
            if (qubits.size() <= 1) {
              removeQubitButton.setVisible(false);
            }
          }
          if (evaluateButton.isPressed(event.mouseButton.x,
                                       event.mouseButton.y)) {
            QuantumCircuit circuit = toCircuit();
            Eigen::VectorXcd simulatorResult = simulator.run(circuit);
            result = Result(sf::Vector2f(1100, 120), simulatorResult, font);
          }
          if (clearButton.isPressed(event.mouseButton.x, event.mouseButton.y)) {
            clearCircuit();
          }

          PlaceholderGate::setVisible(gateSelected);
        }
      }
    }

    // clear the window with white color
    window.clear(sf::Color::White);

    // draw gates
    pauliX.draw(window);
    pauliY.draw(window);
    pauliZ.draw(window);
    hadamard.draw(window);
    cnot.draw(window);

    // draw line after gates
    window.draw(line);

    // draw the qubit(s)
    for (VisualQubit qubit : qubits) {
      qubit.draw(window);
    }

    // draw the buttons
    importButton.draw(window);
    exportButton.draw(window);
    evaluateButton.draw(window);
    clearButton.draw(window);
    addQubitButton.draw(window);
    removeQubitButton.draw(window);

    result.draw(window);

    // end the current frame
    window.display();
  }

  return 0;
}
