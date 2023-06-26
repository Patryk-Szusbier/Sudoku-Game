#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
import Cell;
import Board;
import TextBox;
import Button;
import Interface;

using namespace sf;
using namespace std;
int main()
{
    bool test = false;
    bool fake = true;
    //Okno programu
    sf::RenderWindow window{ sf::VideoMode{1200,800},"Sudoku" };
    window.setFramerateLimit(60);

    //Wczytywanie czcionek
    sf::Font font;
    if (!font.loadFromFile("./Raleway-Regular.ttf")) {
        // Obsługa błędu ładowania czcionki
        return 1;
    }
    sf::Font font2;
    if (!font2.loadFromFile("./Pacifico.ttf"))
    {
        return 1;
    }
    //textbox
    std::vector<vector<TextBox>> textBoxes;
    vector<Button> Buttons;
    Interface Sud;

    Sud.GenerateTextBox(textBoxes, font);
    Sud.CreateButton(Buttons,font);

    sf::Text text("SUDOKU", font2, 72);
    text.setStyle(sf::Text::Bold );
    text.setPosition(800, 65);
    


    Event event;
    while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) 
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                    for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            textBoxes[i][j].handleClick(mousePosition);
                        }
                    }
                }
                else if (event.type == sf::Event::TextEntered)
                {
                    for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            if (textBoxes[i][j].checkEdit() == false)
                            {
                                Sud.handleText(textBoxes, event);
                            }
                        }
                    }
                }
                for (int i=0;i<Buttons.size();i++)
                {
                    if (i == 0)
                    {
                        Buttons[i].handleEvent(event, window, test);
                    }
                    Buttons[i].handleEvent(event, window, fake);
                }
                if (test)
                {
                    Sud.BoardToTextBox(textBoxes);
                    test = false;
                }
                
            }

        window.clear(sf::Color(101, 101, 102, 255));
        window.draw(text);
        for (int i = 0; i < Buttons.size(); i++)
        {
            Buttons[i].draw(window);
        }
        Sud.DrawTextBox(textBoxes, window);
        window.display();
    }

}

