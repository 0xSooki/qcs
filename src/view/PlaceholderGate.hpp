#ifndef PLACEHOLDER_GATE_HPP
#define PLACEHOLDER_GATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "VisualGateAbstract.hpp"

/**
 * @class PlaceholderGate
 * @brief A class visualizing a quantum gate in GUI.
 */
class PlaceholderGate : public VisualGateAbstract {
  private:
    static bool visible_;
    
  public:
    PlaceholderGate() {
      gate_.setSize(sf::Vector2f(size_, size_));
      gate_.setFillColor(sf::Color(255, 0 , 0 , 100));
    }

    /**
    * @brief Constructs a PlaceholderGate with a specified position and abbreviation of the gate.
    *
    * Initializes a square to specified position.
    *
    * @param pos Position where the gate should be drawn in GUI.
    */
    PlaceholderGate(const sf::Vector2f& pos) {
      gate_.setSize(sf::Vector2f(size_, size_));
      gate_.setFillColor(sf::Color(255, 0 , 0 , 0));
      gate_.setPosition(pos);
    }

    /**
    * @brief Destructor for the PlaceholderGate class.
    */
    ~PlaceholderGate() = default;

    /**
    * @brief Draws the gate to the window.
    *
    * @param window Window where the gate will be drawn.
    */
    virtual const void draw(sf::RenderWindow& window) const {
      if (visible_)
        window.draw(gate_);
    }

    void moveTo(sf::Vector2f newPosition) {
      gate_.setPosition(newPosition);
    }

    /**
    * @brief Setter for 'visible' variable
    *
    * @param visible the value to be set
    */
    static void setVisible(bool visible) {      
      /*if (visible) 
        gate_.setFillColor(sf::Color(255, 0 , 0 , 100));
      else
        gate_.setFillColor(sf::Color(255, 0 , 0 , 0));*/
      visible_ = visible;
    }

    bool isVisible() {
      return visible_;
    }
};

bool PlaceholderGate::visible_ = false;
//sf::RectangleShape PlaceholderGate::gate_(sf::Vector2f(1, 1));

#endif // PLACEHOLDER_GATE_HPP