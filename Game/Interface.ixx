#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <iostream>
#include <string>
import Cell;
import Board;
import TextBox;
import Button;

using namespace std;

export module Interface;

export class Interface
{
    Board Bor;
public:
    //Stworzenie przycisków
    void CreateButton(vector<Button>& Buttons, sf::Font& font)
    {
        Button Generate(sf::Vector2f(825, 250), sf::Vector2f(250, 75), sf::Color::Red, sf::Color::Green, sf::Color::Blue,
            bind(&Board::generate, &Bor), "Generuj");

        //Problem, z bind Nie chce dzia³aæ z this
       Button Save(sf::Vector2f(825.00, 350.0), sf::Vector2f(250, 50), sf::Color::Red, sf::Color::Green, sf::Color::Blue,
          bind(&Board::saveToFile, &Bor), "Zapisz");

        Generate.setFont(font);
         Save.setFont(font);
         Buttons.push_back(Generate);
         Buttons.push_back(Save);
    }
    //Wygenerowanie planszy TextBoxów
	void GenerateTextBox(vector<vector<TextBox>>& textBoxes, sf::Font& font)
	{
        
        int posX = 100;
        int posY = 100;
        for (int i = 0; i < 9; i++)
        {
            std::vector<TextBox> row;
            for (int j = 0; j < 9; j++)
            {
                TextBox text(font, 24, sf::Vector2f(posX, posY), sf::Color::White, sf::Color::Black, sf::Color::Black, sf::Vector2f(50, 50), 3.f, i, j);
                row.push_back(text);
                if ((j + 1) % 3 == 0)
                {
                    posX += 65;
                }
                else
                {
                    posX += 55;
                }

            }
            textBoxes.push_back(row);
            if ((i + 1) % 3 == 0)
            {
                posY += 65;
            }
            else
            {
                posY += 55;
            }
            posX = 100;
        }
	}
    void StandardBlocked(vector<vector<TextBox>>& textBoxes)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                textBoxes[i][j].setEdit(!Bor.GetEditable(i,j));
            }
        }
    }
    //Obs³uga naciœniêcia TextBoxa
    void handleClick(vector<vector<TextBox>>& textBoxes,sf::Vector2f mousePosition)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                textBoxes[i][j].handleClick(mousePosition);
            }
        }
    }
    //Obs³uga zdarzeñ TextBox
    void handleText(vector<vector<TextBox>>& textBoxes, sf::Event event)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (Bor.GetEditable(i,j) != false)
                {
                    textBoxes[i][j].handleTextEntry(event);
                    //Bor.SetValue(i, j, event.text.unicode);
                    if (event.type == sf::Event::TextEntered && event.text.unicode != '\b')
                    {
                        string tex;
                        tex += static_cast<char>(event.text.unicode);
                        int x = stoi(tex);
                        if (textBoxes[i][j].Active() && Bor.isValid(i, j, x) == true)
                        {
                            Bor.SetValue(i, j, x);
                            textBoxes[i][j].SetFillColor(sf::Color::Green);
                        }
                        if(textBoxes[i][j].Active() && Bor.isValid(i, j, x) == false)
                        {
                            textBoxes[i][j].SetFillColor(sf::Color::Red);
                        }
                    }
                    }
                    

            }
        }
    }
    //Przepisanie planszy z klasy Board do TextBoxów
    void BoardToTextBox(vector<vector<TextBox>>& textBoxes)
    {
        StandardBlocked(textBoxes);

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                int temp = Bor.GetValue2(i, j);
                textBoxes[i][j].Reset();
                if (temp != 0)
                {
                    textBoxes[i][j].SetString(temp);
                    textBoxes[i][j].SetFillColor(sf::Color::Black);
                }
            }
        }
    }
    //Rysowanie na ekranie Textboxów
    void DrawTextBox(vector<vector<TextBox>>& textBoxes, sf::RenderWindow& target)
    {
        for (const auto& row : textBoxes)
        {
            for (const auto& textBox : row)
            {
                target.draw(textBox);
            }
        }
    }
};