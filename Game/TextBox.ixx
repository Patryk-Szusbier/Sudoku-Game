#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>

using namespace std;

export module TextBox;

export class TextBox : public sf::Drawable
{
public:
    TextBox(sf::Font& font, unsigned int fontSize, sf::Vector2f position, sf::Color fillColor, sf::Color textColor, sf::Color outlineColor,sf::Vector2f size, float outlineThickness,int X,int Y)
    {
        text.setFont(font);
        text.setCharacterSize(fontSize);
        text.setPosition(position);
        text.setFillColor(textColor);

        shape.setPosition(position);
        shape.setFillColor(fillColor);
        shape.setOutlineColor(outlineColor);
        shape.setOutlineThickness(outlineThickness);
        shape.setSize(size);
        this->isBlocked = false;
        this->X = X;
        this->Y = Y;
    }
    void SetFillColor(sf::Color Color)
    {
        text.setFillColor(Color);
    }

    void handleClick(sf::Vector2f mousePosition)
    {
        if (shape.getGlobalBounds().contains(mousePosition))
        {
            isActive = true;
        }
        else
        {
            isActive = false;
        }
    }

    void handleTextEntry(sf::Event event)
    {
            if (isActive && event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !textString.empty())
                {
                    textString.pop_back(); // Backspace character, remove last character from string
                }
                else if (event.text.unicode >= '1' && event.text.unicode <= '9') // Accept only numbers from 1 to 9
                {
                    if (textString.size() == 0)
                    {
                        textString += static_cast<char>(event.text.unicode);
                    }

                }
                text.setString(textString);
            }

        
    }
    string GetString()
    {
        return text.getString();
    }

    bool checkEdit()
    {
        return isBlocked;
    }
    //test
    void setEdit(bool ed)
    {
        isBlocked = ed;
    }
    void Reset()
    {
        textString.clear();
        text.setString(textString);
    }
    bool Active()
    {
        return isActive;
    }
    void SetString(int number)
    {
        string temp = to_string(number);
        text.setString(temp);
        this->isBlocked = true;
    }
    int ReturnX()
    {
        return X;
    }
    int ReturnY()
    {
        return Y;
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
        target.draw(text, states);
    }

private:
    sf::Text text;
    sf::RectangleShape shape;
    string textString;
    bool isActive = false;
    bool isBlocked;
    int X;
    int Y;
};