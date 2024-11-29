#ifndef VISUAL_CNOT_HPP
#define VISUAL_CNOT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class VisualGate
 * @brief A class visualizing a quantum gate in GUI.
 */
class VisualCNOT {
  private:
    sf::CircleShape control_;
    sf::CircleShape target_;
    sf::RectangleShape connector_;

  public:
    /**
    * @brief Constructs a VisualGate with a specified position and abbreviation of the gate.
    *
    * Initializes a square to specified position with specified abbreviation inside of the square.
    *
    * @param pos Position where the gate should be drawn in GUI.
    */
    VisualCNOT(const sf::Vector2f& controlPos, const sf::Vector2f& targetPos) {
      control_.setRadius(15);
      control_.setFillColor(sf::Color::Black);
      control_.setPosition(controlPos);
      control_.setOrigin(control_.getGlobalBounds().width / 2.f + control_.getLocalBounds().left, control_.getGlobalBounds().height / 2.f + control_.getLocalBounds().top);

      target_.setRadius(20);
      target_.setFillColor(sf::Color::White);
      target_.setPosition(targetPos);
      target_.setOutlineThickness(5);
      target_.setOutlineColor(sf::Color::Black);
      target_.setOrigin(target_.getGlobalBounds().width / 2.f + target_.getLocalBounds().left, target_.getGlobalBounds().height / 2.f + target_.getLocalBounds().top);

      connector_.setSize(sf::Vector2f((controlPos.y - targetPos.y), 4));
      connector_.setOrigin(connector_.getPosition() + sf::Vector2f(2, 0));
      connector_.setFillColor(sf::Color::Black);
      connector_.setPosition(controlPos);
      connector_.rotate(-90.f);
    }

    /**
    * @brief Default destructor for the VisualGate class.
    */
    virtual ~VisualCNOT() = default;

    /**
    * @brief Draws the gate to the window.
    *
    * @param window Window where the gate will be drawn.
    */
    const void draw(sf::RenderWindow& window) const {
      window.draw(control_);
      window.draw(target_);
      window.draw(connector_);
    }

    /**
    * @brief Get the position of the control dot.
    *
    * @return 2D vector of the position.
    */
    const sf::Vector2f getControlPosition() const {
      return control_.getPosition();
    }

    /**
    * @brief Get the position of the target dot.
    *
    * @return 2D vector of the position.
    */
    const sf::Vector2f getTargetPosition() const {
      return target_.getPosition();
    }
};

#endif // VISUAL_CNOT_HPP