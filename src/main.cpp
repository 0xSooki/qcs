#include <SFML/Graphics.hpp>
#include <filesystem>

#include "view/VisualCNOT.hpp"
#include "../libs/tinyfiledialogs/tinyfiledialogs.hpp"

#include "view/Button.hpp"
#include "view/PlaceholderGate.hpp"
#include "view/Result.hpp"
#include "view/VisualGate.hpp"
#include "view/VisualQubit.hpp"

#include "controller/QuantumCircuit.hpp"
#include "controller/Simulator.hpp"

#include "gates/PauliGates.hpp"
#include "gates/Hadamard.hpp"

int windowHeight = 800;
int windowWidth = 1400;
bool gateSelected = false;
sf::Font font;
std::vector<VisualQubit> qubits;
bool cnotControl = false;
std::shared_ptr<VisualQubit> controlQubit;

int main() {
    std::filesystem::path fontPath = "../../resources/Roboto-Bold.ttf";

    if (!font.loadFromFile(fontPath)) {
        std::cout << "File path " << fontPath << " at absolute location "
                  << absolute(fontPath) << " does not exist\n";
    }
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Quantum Circuit Simulator");

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

    qubits.push_back(VisualQubit(sf::Vector2f(260, 140), font));
    Button addQubit(sf::Vector2f(260, 250), "Add Qubit", font);
    Button removeQubit(sf::Vector2f(400, 250), "Remove Qubit", font, false);

    Button importButton(sf::Vector2f(windowWidth - 20, 20) - sf::Vector2f(190, 0), "Import from file", font);
    Button exportButton(sf::Vector2f(windowWidth - 20, 20) - sf::Vector2f(360, 0), "Export to file", font);
    Button evaluateButton(sf::Vector2f(160, 20), "Evaluate circuit", font);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
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

                        gateSelected = pauliX.getSelected();
                    }
                    if (pauliY.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(!pauliY.getSelected());
                        pauliZ.setSelected(false);
                        hadamard.setSelected(false);
                        cnot.setSelected(false);

                        gateSelected = pauliY.getSelected();
                    }
                    if (pauliZ.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(!pauliZ.getSelected());
                        hadamard.setSelected(false);
                        cnot.setSelected(false);

                        gateSelected = pauliZ.getSelected();
                    }
                    if (hadamard.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(false);
                        hadamard.setSelected(!hadamard.getSelected());
                        cnot.setSelected(false);

                        gateSelected = hadamard.getSelected();
                    }
                    if (cnot.isPressed(event.mouseButton.x, event.mouseButton.y) && qubits.size() > 1) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(false);
                        hadamard.setSelected(false);
                        cnot.setSelected(!cnot.getSelected());

                        gateSelected = cnot.getSelected();
                    }
                    for (auto qubit = qubits.begin() ; qubit != qubits.end() ; qubit++) {
                        if (qubit->isPlaceholderClicked(event.mouseButton.x, event.mouseButton.y) && gateSelected) {
                            if (pauliX.getSelected())
                                qubit->addGate("X", font);
                            else if (pauliY.getSelected())
                                qubit->addGate("Y", font);
                            else if (pauliZ.getSelected())
                                qubit->addGate("Z", font);
                            else if (hadamard.getSelected())
                                qubit->addGate("H", font);
                            else if (cnot.getSelected()) {
                                if (cnotControl) {
                                    qubit->addCNOTGate(controlQubit);
                                    cnotControl = false;
                                } else {
                                    controlQubit = std::make_shared<VisualQubit>(std::move(*qubit));
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
                        if (qubit->isInitialStageClicked(event.mouseButton.x, event.mouseButton.y)) {
                            qubit->switchInitialState();
                        }
                    }
                    if (importButton.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        std::cout << "Import button is pressed" << std::endl;
                        char const * selection = tinyfd_openFileDialog(
                            "Import a circuit from", // title
                            NULL, // optional initial directory
                            0, // number of filter patterns
                            NULL, // char const * lFilterPatterns[2] = { "*.txt", "*.jpg" };
                            NULL, // optional filter description
                            0 // forbids multiple selections
                        );

                        std::cout << selection << std::endl;

                        // Use the selection like this: readFile(selection);
                        // And create it visually (probably some function to parse file)
                    }
                    if (exportButton.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        std::cout << "Export button is pressed" << std::endl;
                        // Here the function for saving the file
                    }
                    if (addQubit.isPressed(event.mouseButton.x, event.mouseButton.y) && qubits.size() < 5) {
                        qubits.push_back(VisualQubit(addQubit.getPosition(), font));
                        addQubit.moveTo(addQubit.getPosition() + sf::Vector2f(0, 110));
                        removeQubit.moveTo(removeQubit.getPosition() + sf::Vector2f(0, 110));
                        removeQubit.setVisible(true);
                    }
                    if (removeQubit.isPressed(event.mouseButton.x, event.mouseButton.y) && removeQubit.isVisible()) {
                        qubits.pop_back();
                        addQubit.moveTo(addQubit.getPosition() - sf::Vector2f(0, 110));
                        removeQubit.moveTo(removeQubit.getPosition() - sf::Vector2f(0, 110));
                        if (qubits.size() <= 1) {
                            removeQubit.setVisible(false);
                        }
                    }
                    if (evaluateButton.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        QuantumCircuit circuit({qubit.getInitialState()});
                        std::vector<std::pair<std::shared_ptr<Gate>, VisualGate>> gates = qubit.getGates();

                        for (auto it = gates.begin() ; it != gates.end() ; it++) {
                            std::shared_ptr<Gate> ptr = it->first;
                            circuit.addGate(ptr);
                        }

                        Eigen::VectorXcd simulatorResult = simulator.run(circuit);
                        result = Result(sf::Vector2f(260, 240), simulatorResult, font);
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

        result.draw(window);
        addQubit.draw(window);
        removeQubit.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}
