#ifndef VISUAL_QUBIT_HPP
#define VISUAL_QUBIT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "PlaceholderGate.hpp"
#include "VisualGate.hpp"

#include "../gates/Gate.hpp"

/**
 * @class VisualQubit
 * @brief A class visualizing a qubit in GUI.
 */
class VisualQubit
{
private:
  sf::RectangleShape qubit_;
  sf::Text text_;
  int initialState_ = 0;
  std::vector<std::pair<std::shared_ptr<Gate>, VisualGate>> gates_;
  PlaceholderGate placeholder_;

public:
  /**
   * @brief Constructs a VisualQubit with a specified position of the qubit.
   *
   * Initializes a line to specified position with initial state of the qubit before the line.
   *
   * @param pos Position where the qubit should be drawn in GUI.
   * @param font The font that will be used for the texts.
   */
  VisualQubit(const sf::Vector2f &pos, const sf::Font &font)
  {
    qubit_.setSize(sf::Vector2f(800, 5));
    qubit_.setFillColor(sf::Color::Black);
    qubit_.setPosition(pos);

    std::stringstream ss;
    ss << "|" << initialState_ << ">";

    text_.setFont(font);
    text_.setString(ss.str());
    text_.setCharacterSize(32);
    text_.setFillColor(sf::Color::Black);
    text_.setOrigin(text_.getGlobalBounds().width + text_.getLocalBounds().left, text_.getGlobalBounds().height / 2.f + text_.getLocalBounds().top);
    text_.setPosition(qubit_.getPosition() - sf::Vector2f(20, -2));

    placeholder_.moveTo(pos + sf::Vector2f(20, -40));
  }

  /**
   * @brief Default destructor for the VisualQubit class.
   */
  ~VisualQubit() = default;

  /**
   * @brief Draws the initial state, the qubit and it's gates to the window.
   *
   * @param window Window where everything will be drawn.
   */
  const void draw(sf::RenderWindow &window) const
  {
    window.draw(qubit_);
    window.draw(text_);
    for (auto gate : gates_)
    {
      gate.second.draw(window);
    }
    if (gates_.size() < 7)
      placeholder_.draw(window);
  }

    /**
    * @brief Determines if the mouse click happened inside the placeholder gate.
    *
    * @param mouseX Mouse position on x axis.
    * @param mouseY Mouse position on y axis.
    * 
    * @return True if the placeholder gate is clicked, false otherwise.
    */
    const bool isPlaceholderClicked(int mouseX, int mouseY) const {
      return gates_.size() < 7
        ? placeholder_.isPressed(mouseX, mouseY)
        : false;
    }

    /**
    * @brief Switches the initial state of the qubit to be either 0 or 1.
    */
    void switchInitialState()
    {
      initialState_ == 0
          ? initialState_ = 1
          : initialState_ = 0;
  
      std::stringstream ss;
      ss << "|" << initialState_ << ">";
  
      text_.setString(ss.str());
    }

  /**
   * @brief Determines if the mouse click happened inside the initial state text.
   *
   * @param mouseX Mouse position on x axis.
   * @param mouseY Mouse position on y axis.
   *
   * @return True if initial state is clicked, false otherwise.
   */
  const bool isInitialStageClicked(int mouseX, int mouseY) const
  {
    return text_.getGlobalBounds().contains(mouseX, mouseY);
  }

  /**
   * @brief Adds a new visual-logical gate pair to gates_.
   *
   * @param abbreviation Text that will be visible in the gate.
   * @param font The font that will be used inside the gate
   * @param gate The logical gate that will be paired with the visual one
   */
  void addGate(const std::string &abbreviation, const sf::Font &font, std::shared_ptr<Gate> gate)
  {
    std::pair<std::shared_ptr<Gate>, VisualGate> newGate(
        gate,
        VisualGate(placeholder_.getPosition(), abbreviation, font));
    gates_.push_back(newGate);
    placeholder_.moveTo(newGate.second.getPosition() + sf::Vector2f(110, 0));
  }

  /**
   * @brief Get the Gates vector.
   *
   * @return std::vector<std::pair<Gate, VisualGate>>
   */
  std::vector<std::pair<std::shared_ptr<Gate>, VisualGate>> getGates()
  {
    return gates_;
  }

  /**
   * @brief Get the Initial State of the qubit.
   *
   * @return int
   */
  int getInitialState()
  {
    return initialState_;
  }
};

#endif // VISUAL_QUBIT_HPP
