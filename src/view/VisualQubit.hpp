#ifndef VISUAL_QUBIT_HPP
#define VISUAL_QUBIT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "PlaceholderGate.hpp"
#include "VisualGate.hpp"

/**
 * @class VisualQubit
 * @brief A class visualizing a qubit in GUI.
 */
class VisualQubit {
  private:
    sf::RectangleShape qubit_;
    sf::Font font_;
    sf::Text text_;
    std::string initialState_ = "|0>";
    std::vector<VisualGate> gateSlots_;
    PlaceholderGate placeholder_;

  public:
    VisualQubit(const sf::Vector2f& pos) {
      qubit_.setSize(sf::Vector2f(800, 5));
      qubit_.setFillColor(sf::Color::Black);
      qubit_.setPosition(pos);

      if (!font_.loadFromFile("./src/resources/fonts/Roboto-Bold.ttf")) {
          std::cout << "Failed to load the font_" << std::endl;
      }

      text_.setFont(font_);
      text_.setString(initialState_);
      text_.setCharacterSize(32);
      text_.setFillColor(sf::Color::Black);
      text_.setOrigin(text_.getGlobalBounds().width + text_.getLocalBounds().left, text_.getGlobalBounds().height / 2.f + text_.getLocalBounds().top);
      text_.setPosition(qubit_.getPosition() - sf::Vector2f(20, -2));

      placeholder_.moveTo(pos + sf::Vector2f(20, -40));
    }

    /**
    * @brief Destructor for the VisualQubit class.
    */
    ~VisualQubit() = default;

    /**
    * @brief Draws the qubit and it's gates to the window.
    *
    * @param window Window where the qubit and gates will be drawn.
    */
    const void draw(sf::RenderWindow& window) const {
      window.draw(qubit_);
      window.draw(text_);
      for (VisualGate gate : gateSlots_) {
        gate.draw(window);
      }
      if (gateSlots_.size() < 7)
        placeholder_.draw(window);
    }

    const bool isPlaceholderClicked(int mouseX, int mouseY) const {
      return gateSlots_.size() < 7
        ? placeholder_.isPressed(mouseX, mouseY)
        : false;
    }

    void switchInitialState() {
      initialState_ == "|0>"
        ? initialState_ = "|1>"
        : initialState_ = "|0>";

      text_.setString(initialState_);
    }

    const bool isInitialStageClicked(int mouseX, int mouseY) const {
      return text_.getGlobalBounds().contains(mouseX, mouseY);
    }

    void addGate(std::string abbreviation) {
      VisualGate gate(placeholder_.getPosition(), abbreviation);
      gateSlots_.push_back(gate);
      placeholder_.moveTo(gate.getPosition() + sf::Vector2f(110, 0));
    }
};

#endif // VISUAL_QUBIT_HPP