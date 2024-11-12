#include <SFML/Graphics.hpp>

#include "view/VisualGate.hpp"

int main() {
  // create the window
    int windowHeight = 800;
    int windowWidth = 1000;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Quantum Circuit Simulator");

    VisualGate pauliX(sf::Vector2f(20, 20), "X");
    VisualGate pauliY(sf::Vector2f(20, 140), "Y");
    VisualGate pauliZ(sf::Vector2f(20, 260), "Z");
    VisualGate hadamart(sf::Vector2f(20, 380), "H");
    VisualGate cnot(sf::Vector2f(20, 500), "CNOT");

    sf::RectangleShape line(sf::Vector2f(windowHeight, 5.f));
    line.setFillColor(sf::Color::Black);
    line.setPosition(sf::Vector2f(140.f, 0.f));
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
                        pauliX.setSelected(!pauliX.selected);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(false);
                        hadamart.setSelected(false);
                        cnot.setSelected(false);
                    }
                    if (pauliY.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(!pauliY.selected);
                        pauliZ.setSelected(false);
                        hadamart.setSelected(false);
                        cnot.setSelected(false);
                    }
                    if (pauliZ.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(!pauliZ.selected);
                        hadamart.setSelected(false);
                        cnot.setSelected(false);
                    }
                    if (hadamart.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(false);
                        hadamart.setSelected(!hadamart.selected);
                        cnot.setSelected(false);
                    }
                    if (cnot.isPressed(event.mouseButton.x, event.mouseButton.y)) {
                        pauliX.setSelected(false);
                        pauliY.setSelected(false);
                        pauliZ.setSelected(false);
                        hadamart.setSelected(false);
                        cnot.setSelected(!cnot.selected);
                    }
                }
            }
        }

        // clear the window with white color
        window.clear(sf::Color::White);

        // draw everything here...
        // draw gates
        pauliX.draw(window);
        pauliY.draw(window);
        pauliZ.draw(window);
        hadamart.draw(window);
        cnot.draw(window);

        // draw line after gates
        window.draw(line);

        // end the current frame
        window.display();
    }

    return 0;
}