#ifndef RESULT_HPP
#define RESULT_HPP

#include <SFML/Graphics.hpp>
#include <Eigen/Dense>

/**
 * @class Result
 * @brief A class visualizing the result of the quantum computer simulation.
 */
class Result {
  private:
    sf::Text text_;
    sf::Text result_;
    
  public:
    /**
    * @brief Default constructor for Result.
    */
    Result() = default;

    /**
    * @brief Constructs a Result object with a specified position and computation result.
    *
    * Initializes two text blocks with "Result:" and the result provided by the quantum computer simulation.
    *
    * @param pos Position where the "Result:" text should be drawn in GUI.
    * @param result Result that will be visible next to text.
    * @param font The font that will be used for the texts.
    */
    Result(const sf::Vector2f& pos, const Eigen::VectorXcd& result, const sf::Font& font) {
      text_.setFont(font);
      text_.setString("Result:");
      text_.setCharacterSize(32);
      text_.setFillColor(sf::Color::Black);
      text_.setPosition(pos);

      std::stringstream ss;
      ss << result;

      result_.setFont(font);
      result_.setString(ss.str());
      result_.setCharacterSize(32);
      result_.setFillColor(sf::Color::Black);
      result_.setPosition(pos + sf::Vector2f(120, 0));
    }

    /**
    * @brief Default destructor for the Result class.
    */
    virtual ~Result() = default;

    /**
    * @brief Draws the result texts to the window.
    *
    * @param window Window where the texts will be drawn.
    */
    const void draw(sf::RenderWindow& window) const {
      window.draw(text_);
      window.draw(result_);
    }

    /**
    * @brief Moves the result to a specified position.
    *
    * @param newPosition Vector of the position the result will be moved.
    */
    void moveTo(sf::Vector2f newPosition) {
      text_.setPosition(newPosition);
      result_.setPosition(newPosition + sf::Vector2f(120, 0));
    }

    /**
     * @brief Overloaded = operator
     * 
     * @param result Result instance to be copied
     * @return Result& copied Result object
     */
    Result& operator=(const Result& result) {
      if (this != &result) {
          text_ = result.text_;
          result_ = result.result_;
      }
      return *this;
    }
};

#endif // RESULT_HPP