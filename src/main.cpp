#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>

#include "../libs/tinyfiledialogs/tinyfiledialogs.hpp"
#include "gates/Gate.hpp"
#include "gates/RotationGate.hpp"
#include "view/VisualCNOT.hpp"

#include "view/Button.hpp"
#include "view/PlaceholderGate.hpp"
#include "view/Result.hpp"
#include "view/VisualGate.hpp"
#include "view/VisualQubit.hpp"

#include "controller/QuantumCircuit.hpp"
#include "controller/Simulator.hpp"

#include "gates/Hadamard.hpp"
#include "gates/PauliGates.hpp"

QuantumCircuit toCircuit(std::vector<VisualQubit> qubits) {
    QuantumCircuit circuit({qubits[0].getInitialState()});
    std::vector<std::pair<std::shared_ptr<Gate>, VisualGate>> gates = qubits[0].getGates();
    
    for (auto it = gates.begin() ; it != gates.end() ; it++) {
        std::shared_ptr<Gate> ptr = it->first;
        circuit.addGate(ptr);
    }

    return circuit;
}

int windowHeight = 800;
int windowWidth = 1400;
bool gateSelected = false;
char const * fileFilterPatterns[1] = { "*.json" };
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
                          "Quantum Circuit Simulator");

  Simulator simulator;
  Result result;

  VisualGate pauliX(sf::Vector2f(65, 65), "X", font);
  VisualGate pauliY(sf::Vector2f(65, 185), "Y", font);
  VisualGate pauliZ(sf::Vector2f(65, 305), "Z", font);
  VisualGate hadamard(sf::Vector2f(65, 425), "H", font);
  VisualGate cnot(sf::Vector2f(65, 545), "CNOT", font);

  VisualCNOT vis(sf::Vector2f(260, 140), sf::Vector2f(260, 250));

  sf::RectangleShape line(sf::Vector2f(windowHeight, 5));
  line.setFillColor(sf::Color::Black);
  line.setPosition(sf::Vector2f(140, 0));
  line.rotate(90.f);

  qubits.push_back(VisualQubit(sf::Vector2f(260, 140), font, 0));
  Button addQubit(sf::Vector2f(260, 250), "Add Qubit", font);
  Button removeQubit(sf::Vector2f(400, 250), "Remove Qubit", font, false);

  Button importButton(sf::Vector2f(windowWidth - 20, 20) - sf::Vector2f(190, 0),
                      "Import from file", font);
  Button exportButton(sf::Vector2f(windowWidth - 20, 20) - sf::Vector2f(360, 0),
                      "Export to file", font);
  Button evaluateButton(sf::Vector2f(160, 20), "Evaluate circuit", font);
  Button clearButton(sf::Vector2f(360, 20), "Clear circuit", font);

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
                pauliX.setSelected(false);
                pauliY.setSelected(false);
                pauliZ.setSelected(false);
                hadamard.setSelected(false);
                cnot.setSelected(false);
                gateSelected = false;
              }
            }
            if (qubit->isInitialStageClicked(event.mouseButton.x,
                                             event.mouseButton.y)) {
              qubit->switchInitialState();
            }
          }
          if (importButton.isPressed(event.mouseButton.x,
                                     event.mouseButton.y)) {
            std::cout << "Import button is pressed" << std::endl;
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
                            std::vector<std::shared_ptr<Gate>> gates = circuit.getGates();
                            qubit.clearGates();
                            result = Result();

                            for (auto gate : gates) {
                                if (dynamic_cast<const PauliX*>(gate.get())) {
                                    qubit.addGate("X", font, gate);
                                } else if (dynamic_cast<const PauliY*>(gate.get())) {
                                    qubit.addGate("Y", font, gate);
                                } else if (dynamic_cast<const PauliZ*>(gate.get())) {
                                    qubit.addGate("Z", font, gate);
                                } else if (dynamic_cast<const H*>(gate.get())) {
                                    qubit.addGate("H", font, gate);
                                } else if (dynamic_cast<const CNOT*>(gate.get())) {
                                    std::cout << "Add CNOT to the visual circuit" << std::endl;
                                }
                            }
                        }
                    }
                    if (exportButton.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        char const * filename = tinyfd_saveFileDialog(
		                    "Save circuit to", // title
		                    NULL, // optional initial directory
		                    1, // number of filter patterns
		                    fileFilterPatterns, // char const * lFilterPatterns[2] = { "*.txt", "*.jpg" };
		                    NULL // forbids multiple selections
                        );

                        if (filename != NULL) {
                            QuantumCircuit circuit = toCircuit({qubit});
                            writeCircuitToFile(circuit, filename);
                        }
                    }
                    if (evaluateButton.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        QuantumCircuit circuit = toCircuit({qubit});
                        Eigen::VectorXcd simulatorResult = simulator.run(circuit);
                        result = Result(sf::Vector2f(260, 240), simulatorResult, font);
                    }
                    if (clearButton.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        qubit.clearGates();
                        result = Result();
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

    result.draw(window);
    addQubit.draw(window);
    removeQubit.draw(window);

    // end the current frame
    window.display();
  }

  return 0;
}
