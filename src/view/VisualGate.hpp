#ifndef VISUAL_GATE_HPP
#define VISUAL_GATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "VisualGateAbstract.hpp"

/**
 * @class VisualGate
 * @brief A class visualizing a quantum gate in GUI.
 */
class VisualGate : public VisualGateAbstract {
  private:
    sf::Text text_;
    bool selected_ = false;
    
  public:
    /**
    * @brief Constructs a VisualGate with a specified position and abbreviation of the gate.
    *
    * Initializes a square to specified position with specified abbreviation inside of the square.
    *
    * @param pos Position where the gate should be drawn in GUI.
    * @param abbreviation Text that will be visible inside the gate square.
    */
    VisualGate(const sf::Vector2f& pos, const std::string& abbreviation, const sf::Font& font) {
      gate_.setSize(sf::Vector2f(size_, size_));
      gate_.setFillColor(sf::Color::White);
      gate_.setPosition(pos);
      gate_.setOutlineThickness(5.f);
      gate_.setOutlineColor(sf::Color::Black);

      text_.setFont(font);
      text_.setString(abbreviation);
      text_.setCharacterSize(32);
      text_.setFillColor(sf::Color::Black);
      text_.setOrigin(text_.getGlobalBounds().width / 2.f + text_.getLocalBounds().left, text_.getGlobalBounds().height / 2.f + text_.getLocalBounds().top);
      text_.setPosition(gate_.getPosition() + (gate_.getSize() / 2.f));
    }

    /**
    * @brief Default destructor for the VisualGate class.
    */
    virtual ~VisualGate() = default;

    /**
    * @brief Draws the gate to the window.
    *
    * @param window Window where the gate will be drawn.
    */
    const void draw(sf::RenderWindow& window) const override {
      window.draw(gate_);
      window.draw(text_);
    }

    /**
    * @brief Moves the gate to a specified position.
    *
    * @param newPosition Vector of the position the gate will be moved.
    */
    void moveTo(sf::Vector2f newPosition) override {
      gate_.setPosition(newPosition);
      text_.setPosition(newPosition + (gate_.getSize() / 2.f));
    }

    /**
    * @brief Getter for 'selected_' variable.
    *
    * @return True or false, depending on the value of 'selected_'.
    */
    const bool getSelected() const {
      return selected_;
    }

    /**
    * @brief Setter for 'selected_' variable.
    *
    * @param selected The value to be set.
    */
    void setSelected(bool selected) {
      if (selected) 
        gate_.setFillColor(sf::Color::Red);
      else
        gate_.setFillColor(sf::Color::White);
      
      selected_ = selected;
    }
};

#endif // VISUAL_GATE_HPP
