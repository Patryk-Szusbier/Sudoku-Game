#include <SFML/Graphics.hpp>
#include <functional>

export module Button;



export class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& clickColor, std::function<void()> onClick, const std::string& text = "")
        : position(position), size(size), idleColor(idleColor), hoverColor(hoverColor), clickColor(clickColor), currentState(State::Idle), onClick(onClick)
    {
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(idleColor);

        if (!text.empty()) {
            setText(text);
        }
    }

    void setText(const std::string& text, unsigned int characterSize = 28, const sf::Color& textColor = sf::Color::White)
    {
        buttonText.setString(text);
        buttonText.setCharacterSize(characterSize);
        buttonText.setFillColor(textColor);

        // Ustalamy punkt odniesienia tekstu na jego œrodek
        sf::FloatRect textBounds = buttonText.getLocalBounds();
        buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

        // Ustalamy pozycjê tekstu na œrodek przycisku
        sf::Vector2f textPosition = position + sf::Vector2f(size.x / 3.75f, size.y / 4.75f);
        buttonText.setPosition(textPosition);
    }

    void setFont(const sf::Font& font)
    {
        buttonText.setFont(font);
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window, bool& test)
    {
        if (event.type == sf::Event::MouseMoved) {
            if (shape.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                currentState = State::Hover;
                shape.setFillColor(hoverColor);
            }
            else {
                currentState = State::Idle;
                shape.setFillColor(idleColor);
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (shape.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                currentState = State::Clicked;
                shape.setFillColor(clickColor);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (shape.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                currentState = State::Hover;
                shape.setFillColor(hoverColor);
                if (onClick) {
                    onClick(); // Wywo³anie podanej funkcji po klikniêciu przycisku
                    test = true;
                }
            }
            else {
                currentState = State::Idle;
                shape.setFillColor(idleColor);
            }
        }
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(shape);
        window.draw(buttonText);
    }

private:
    enum class State {
        Idle,
        Hover,
        Clicked
    };

    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color clickColor;
    State currentState;
    sf::RectangleShape shape;
    std::function<void()> onClick;

    sf::Text buttonText;
};

