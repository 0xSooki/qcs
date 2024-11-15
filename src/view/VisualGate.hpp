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
    sf::Font font_;
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
    VisualGate(const sf::Vector2f& pos, const std::string& abbreviation) {
      gate_.setSize(sf::Vector2f(size_, size_));
      gate_.setFillColor(sf::Color::White);
      gate_.setPosition(pos);
      gate_.setOutlineThickness(5.f);
      gate_.setOutlineColor(sf::Color::Black);

      if (!font_.loadFromFile("./src/resources/fonts/Roboto-Bold.ttf")) {
          std::cout << "Failed to load the font" << std::endl;
      }

      text_.setFont(font_);
      text_.setString(abbreviation);
      text_.setCharacterSize(32);
      text_.setFillColor(sf::Color::Black);
      text_.setOrigin(text_.getGlobalBounds().width / 2.f + text_.getLocalBounds().left, text_.getGlobalBounds().height / 2.f + text_.getLocalBounds().top);
      text_.setPosition(gate_.getPosition() + (gate_.getSize() / 2.f));
    }

    VisualGate() {}

    /**
    * @brief Destructor for the VisualGate class.
    */
    virtual ~VisualGate() = default;

    VisualGate(const VisualGate&) = default;
    VisualGate& operator=(const VisualGate&) = default;

    /**
    * @brief Draws the gate to the window.
    *
    * @param window Window where the gate will be drawn.
    */
    const void draw(sf::RenderWindow& window) const override {
      window.draw(gate_);
      window.draw(text_);
    }

    void moveTo(sf::Vector2f newPosition) override {
      gate_.setPosition(newPosition);
      text_.setPosition(newPosition + (gate_.getSize() / 2.f));
    }

    const bool getSelected() const {
      return selected_;
    }

    /**
    * @brief Setter for 'selected' variable
    *
    * @param selected the value to be set
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