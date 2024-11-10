#ifndef VISUAL_GATE_HPP
#define VISUAL_GATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class VisualGate
 * @brief A class visualizing a quantum gate in GUI.
 *
 * The Gate class extends Eigen's `MatrixXcd` class to represent complex-valued
 * square matrices.
 * This class initializes a matrix with a specified dimension and sets all
 * elements to zero by default.
 */
class VisualGate {
  private:
    sf::RectangleShape gate;
    sf::Text text;
    sf::Font font;
    int size = 90;
    
  public:
    bool selected = false;

    /**
    * @brief Constructs a VisualGate with a specified position and abbreviation of the gate.
    *
    * Initializes a square to specified position with specified abbreviation inside of the square.
    *
    * @param pos Position where the gate should be drawn in GUI.
    * @param abbreviation Text that will be visible inside the gate square.
    */
    VisualGate(sf::Vector2f pos, std::string abbreviation) {
      gate.setSize(sf::Vector2f(size, size));
      gate.setFillColor(sf::Color::White);
      gate.setPosition(pos);
      gate.setOutlineThickness(5.f);
      gate.setOutlineColor(sf::Color::Black);

      if (!font.loadFromFile("./src/resources/fonts/Roboto-Bold.ttf")) {
          std::cout << "Failed to load the font" << std::endl;
      }

      text.setFont(font);
      text.setString(abbreviation);
      text.setCharacterSize(32);
      text.setFillColor(sf::Color::Black);
      text.setOrigin(text.getGlobalBounds().width / 2.f + text.getLocalBounds().left, text.getGlobalBounds().height / 2.f + text.getLocalBounds().top);
      text.setPosition(gate.getPosition() + (gate.getSize() / 2.f));
    }

    /**
    * @brief Destructor for the VisualGate class.
    */
    ~VisualGate() = default;

    /**
    * @brief Draws the gate to the window.
    *
    * @param window Window where the gate will be drawn.
    */
    void draw(sf::RenderWindow& window) {
      window.draw(gate);
      window.draw(text);
    }

    /**
    * @brief Checks if the mouse click happened inside the gate
    *
    * @param mouseX Position where the gate should be drawn in GUI.
    * @param mouseY Text that will be visible inside the gate square.
    * 
    * @return true if the click was inside the gate, otherwise false
    */
    bool isPressed(int mouseX, int mouseY) {
      int gateX = gate.getPosition().x;
      int gateY = gate.getPosition().y;

      if ((gateX <= mouseX && mouseX <= (gateX + size)) && (gateY <= mouseY && mouseY <= (gateY + size)))
        return true;
      else
        return false;
    }

    /**
    * @brief Setter for 'selected' variable
    *
    * @param select the value to be set
    */
    void setSelected(bool select) {
      if (select) 
        gate.setFillColor(sf::Color::Red);
      else
        gate.setFillColor(sf::Color::White);
      
      selected = select;
    }
};

#endif // VISUAL_GATE_HPP