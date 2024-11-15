#include <SFML/Graphics.hpp>

#include "view/VisualGate.hpp"
#include "view/VisualQubit.hpp"
#include "view/PlaceholderGate.hpp"

int main() {
  // create the window
    int windowHeight = 800;
    int windowWidth = 1400;
    bool gateSelected = false;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Quantum Circuit Simulator");

    VisualGate pauliX(sf::Vector2f(20, 20), "X");
    VisualGate pauliY(sf::Vector2f(20, 140), "Y");
    VisualGate pauliZ(sf::Vector2f(20, 260), "Z");
    VisualGate hadamard(sf::Vector2f(20, 380), "H");
    VisualGate cnot(sf::Vector2f(20, 500), "CNOT");

    VisualQubit qubit(sf::Vector2f(260, 140));

    sf::RectangleShape line(sf::Vector2f(windowHeight, 5));
    line.setFillColor(sf::Color::Black);
    line.setPosition(sf::Vector2f(140, 0));
    line.rotate(90.f);

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
                            qubit.addGate("X");
                        else if (pauliY.getSelected())
                            qubit.addGate("Y");
                        else if (pauliZ.getSelected())
                            qubit.addGate("Z");
                        else if (hadamard.getSelected())
                            qubit.addGate("H");
                        else if (cnot.getSelected())
                            qubit.addGate("CNOT");

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

        // end the current frame
        window.display();
    }

    return 0;
}