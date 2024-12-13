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
      gate_.setOrigin(gate_.getSize() / 2.f);
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
      gate_.setOrigin(gate_.getSize() / 2.f);
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
    * @brief Static setter for 'visible_' variable
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

    /**
     * @brief Get the size of a gate object
     * 
     * @return const sf::Vector2f size of the gate
     */
    const sf::Vector2f getSize() const {
      return gate_.getSize();
    }
};

bool PlaceholderGate::visible_ = false;

#endif // PLACEHOLDER_GATE_HPP