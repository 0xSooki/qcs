#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class Button
 * @brief A class visualizing a button in GUI.
 */
class Button {
  private:
    sf::RectangleShape button_;
    sf::Text text_;
    sf::Vector2f size_;
    bool visible_;
    
  public:
    /**
    * @brief Constructs a Button with a specified position and text of the button.
    *
    * Initializes a rectangleShape to specified position with specified text inside of the rectangleShape.
    *
    * @param pos Position where the button should be drawn in GUI.
    * @param text Text that will be visible inside the button.
    * @param font The font that will be used for the button texts.
    * @param visible Determines whether the button will be visible in UI, delauts to true.
    */
    Button(const sf::Vector2f& pos, const std::string& text, const sf::Font& font, bool visible = true) {
      text_.setFont(font);
      text_.setString(text);
      text_.setCharacterSize(24);
      text_.setFillColor(sf::Color::Black);
      text_.setOrigin(text_.getGlobalBounds().width / 2.f + text_.getLocalBounds().left, text_.getGlobalBounds().height / 2.f + text_.getLocalBounds().top);

      size_ = sf::Vector2f(text_.getGlobalBounds().width, text_.getGlobalBounds().height) + sf::Vector2f(15, 15);

      button_.setSize(size_);
      button_.setFillColor(sf::Color::White);
      button_.setPosition(pos);
      button_.setOutlineThickness(3.f);
      button_.setOutlineColor(sf::Color::Black);

      text_.setPosition(button_.getPosition() + (size_ / 2.f));

      visible_ = visible;
    }

    /**
    * @brief Default destructor for the Button class.
    */
    ~Button() = default;

    /**
    * @brief Draws the button with the text to the window.
    *
    * @param window Window where the button will be drawn.
    */
    const void draw(sf::RenderWindow& window) const {
      if (visible_) {
        window.draw(button_);
        window.draw(text_);
      }
    }

    /**
    * @brief Moves the button to a specified position.
    *
    * @param newPosition Vector of the position the button will be moved.
    */
    void moveTo(sf::Vector2f newPosition) {
      button_.setPosition(newPosition);
      text_.setPosition(newPosition + (size_ / 2.f));
    }

    /**
    * @brief Getter for the position of the button.
    *
    * @return 2D vector of the position.
    */
    const sf::Vector2f getPosition() const {
      return button_.getPosition();
    }

    /**
    * @brief Checks if the mouse click happened inside the button.
    *
    * @param mouseX Mouse position on x axis.
    * @param mouseY Mouse position on y axis.
    * 
    * @return True if the click was inside the button rectangle, otherwise false.
    */
    bool isPressed(int mouseX, int mouseY) const {
      int gateX = button_.getPosition().x;
      int gateY = button_.getPosition().y;

      if ((gateX <= mouseX && mouseX <= (gateX + size_.x)) && (gateY <= mouseY && mouseY <= (gateY + size_.y)))
        return true;
      else
        return false;
    }

    /**
    * @brief Setter for 'visible_' variable
    *
    * @param visible the value to be set
    */
    void setVisible(bool visible) {      
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

#endif // BUTTON_HPP