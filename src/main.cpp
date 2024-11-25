#include <SFML/Graphics.hpp>
#include <filesystem>

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

int main() {
  // create the window
    int windowHeight = 800;
    int windowWidth = 1400;
    bool gateSelected = false;
    sf::Font font;

    std::filesystem::path fontPath = "../../resources/Roboto-Bold.ttf";

    if (!font.loadFromFile(fontPath)) {
        std::cout << "File path " << fontPath << " at absolute location "
                  << absolute(fontPath) << " does not exist\n";
    }
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Quantum Circuit Simulator");

    Simulator simulator;
    Result result;

    VisualGate pauliX(sf::Vector2f(20, 20), "X", font);
    VisualGate pauliY(sf::Vector2f(20, 140), "Y", font);
    VisualGate pauliZ(sf::Vector2f(20, 260), "Z", font);
    VisualGate hadamard(sf::Vector2f(20, 380), "H", font);
    VisualGate cnot(sf::Vector2f(20, 500), "CNOT", font);

    sf::RectangleShape line(sf::Vector2f(windowHeight, 5));
    line.setFillColor(sf::Color::Black);
    line.setPosition(sf::Vector2f(140, 0));
    line.rotate(90.f);

    VisualQubit qubit(sf::Vector2f(260, 140), font);

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
                    if (cnot.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(false);
                        hadamard.setSelected(false);
                        cnot.setSelected(!cnot.getSelected());

                        gateSelected = cnot.getSelected();
                    }
                    if (qubit.isPlaceholderClicked(event.mouseButton.x, event.mouseButton.y) && gateSelected) {
                        if (pauliX.getSelected())
                            qubit.addGate("X", font, PauliX({0}));
                        else if (pauliY.getSelected())
                            qubit.addGate("Y", font, PauliY({0}));
                        else if (pauliZ.getSelected())
                            qubit.addGate("Z", font, PauliZ({0}));
                        else if (hadamard.getSelected())
                            qubit.addGate("H", font, H({0}));
                        //else if (cnot.getSelected())
                            //qubit.addGate("CNOT", font, );

                        pauliX.setSelected(false);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(false);
                        hadamard.setSelected(false);
                        cnot.setSelected(false);
                        gateSelected = false;
                    }
                    if (qubit.isInitialStageClicked(event.mouseButton.x, event.mouseButton.y)) {
                        qubit.switchInitialState();
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
                    if (evaluateButton.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        QuantumCircuit circuit(1);
                        std::vector<std::pair<Gate, VisualGate>> gates = qubit.getGates();

                        for (auto it = gates.begin() ; it != gates.end() ; it++) {
                            std::shared_ptr<Gate> ptr = std::make_shared<Gate>(std::move(it->first));
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
        qubit.draw(window);

        // draw the buttons
        importButton.draw(window);
        exportButton.draw(window);
        evaluateButton.draw(window);

        result.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}