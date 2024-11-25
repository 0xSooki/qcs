#ifndef PLACEHOLDER_GATE_HPP
#define PLACEHOLDER_GATE_HPP

#include <SFML/Graphics.hpp>

#include "VisualGateAbstract.hpp"

/**
 * @class PlaceholderGate
 * @brief A class visualizing a placeholder gate in GUI.
 */
class PlaceholderGate : public VisualGateAbstract {
  private:
    static bool visible_;
    
  public:
    /**
    * @brief Default constructor for PlaceholderGate.
    */
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
    * @brief Default destructor for the PlaceholderGate class.
    */
    virtual ~PlaceholderGate() = default;

    /**
    * @brief Draws the placeholder gate to the window if it is set to be visible.
    *
    * @param window Window where the gate will be drawn.
    */
    const void draw(sf::RenderWindow& window) const override {
      if (visible_)
        window.draw(gate_);
    }

    /**
    * @brief Moves the placeholder gate to a specified position.
    *
    * @param newPosition Vector of the position the gate will be moved.
    */
    void moveTo(sf::Vector2f newPosition) override {
      gate_.setPosition(newPosition);
    }

    /**
    * @brief Setter for 'visible_' variable
    *
    * @param visible the value to be set
    */
    static void setVisible(bool visible) {      
      visible_ = visible;
    }

    /**
    * @brief Getter for 'visible_' variable
    * 
    * @return True or false, depending on the value of 'visible_'.
    */
    const bool isVisible() const {
      return visible_;
    }
};

bool PlaceholderGate::visible_ = false;

#endif // PLACEHOLDER_GATE_HPP