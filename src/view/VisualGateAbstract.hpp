#ifndef VISUAL_GATE_ABSTRACT_HPP
#define VISUAL_GATE_ABSTRACT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class VisualGateAbstract
 * @brief A class visualizing a quantum gate in GUI.
 */
class VisualGateAbstract {
  protected:
    sf::RectangleShape gate_;
    int size_ = 90;
    
  public:
    /**
    * @brief Constructs a VisualGate with a specified position and abbreviation of the gate.
    *
    * Initializes a square to specified position with specified abbreviation inside of the square.
    *
    * @param pos Position where the gate should be drawn in GUI.
    */
    VisualGateAbstract() = default;

    /**
    * @brief Destructor for the VisualGate class.
    */
    virtual ~VisualGateAbstract() = default;

    /**
    * @brief Draws the gate to the window.
    *
    * @param window Window where the gate will be drawn.
    */
    virtual const void draw(sf::RenderWindow& window) const = 0;

    /**
    * @brief Checks if the mouse click happened inside the gate
    *
    * @param mouseX Position where the gate should be drawn in GUI.
    * @param mouseY Text that will be visible inside the gate square.
    * 
    * @return true if the click was inside the gate, otherwise false
    */
    bool isPressed(int mouseX, int mouseY) const {
      int gateX = gate_.getPosition().x;
      int gateY = gate_.getPosition().y;

      if ((gateX <= mouseX && mouseX <= (gateX + size_)) && (gateY <= mouseY && mouseY <= (gateY + size_)))
        return true;
      else
        return false;
    }

    virtual void moveTo(sf::Vector2f newPosition) = 0;

    const sf::Vector2f getPosition() const {
      return gate_.getPosition();
    }
};

#endif // VISUAL_GATE_ABSTRACT_HPP