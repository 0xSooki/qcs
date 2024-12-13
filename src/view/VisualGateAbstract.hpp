#ifndef VISUAL_GATE_ABSTRACT_HPP
#define VISUAL_GATE_ABSTRACT_HPP

#include <SFML/Graphics.hpp>

/**
 * @class VisualGateAbstract
 * @brief An abstract class for visual gate-like classes.
 */
class VisualGateAbstract {
  protected:
    sf::RectangleShape gate_;
    int size_ = 90;
    
  public:
    /**
    * @brief Default constructor for VisualGateAbstract class
    */
    VisualGateAbstract() = default;

    /**
    * @brief Default destructor for the VisualGate class.
    */
    virtual ~VisualGateAbstract() = default;

    /**
    * @brief Pure virtual function for drawing the VisualGateAbstract to the screen.
    *
    * @param window Window where the VisualGateAbstract will be drawn.
    */
    virtual const void draw(sf::RenderWindow& window) const = 0;

    /**
    * @brief Pure virtual function for moving the gate to a specified location.
    *
    * @param newPosition Vector of the position the gate will be moved.
    */
    virtual void moveTo(sf::Vector2f newPosition) = 0;

    /**
    * @brief Checks if the mouse click happened inside the abstract gate.
    *
    * @param mouseX Mouse position on x axis.
    * @param mouseY Mouse position on y axis.
    * 
    * @return True if the click was inside the gate, otherwise false.
    */
    bool isPressed(int mouseX, int mouseY) const {
      int gateX = gate_.getPosition().x;
      int gateY = gate_.getPosition().y;

      if (((gateX - (size_ / 2)) <= mouseX && mouseX <= (gateX + (size_ / 2))) && ((gateY - (size_ / 2)) <= mouseY && mouseY <= (gateY + (size_ / 2))))
        return true;
      else
        return false;
    }

    /**
    * @brief Getter for the position of the gate.
    *
    * @return 2D vector of the position.
    */
    const sf::Vector2f getPosition() const {
      return gate_.getPosition();
    }
};

#endif // VISUAL_GATE_ABSTRACT_HPP
