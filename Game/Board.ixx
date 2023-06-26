#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>
#include <regex>
#include <ranges>
#include <string>
#include <cstdlib>
#include <ctime>
#include <future>
#include <random>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

import Cell;
import TextBox;
export module Board;

using namespace std;

export class Board {
public:
    Board()
    {
        board = vector<vector<Cell>>(9);
        board2 = vector<vector<Cell>>(9);
        for (int i = 0; i < 9; i++)
        {
            board[i] = vector<Cell>(9);
            board2[i] = vector<Cell>(9);
        }
    }
    // wczytanie planszy z pliku
    void ReadFromFile()
    {
        sf::RenderWindow window(sf::VideoMode(400, 300), "Save Board");
        string savePath;
        sf::Font font;
        font.loadFromFile("./Raleway-Regular.ttf");
        bool promptt = false;
        // Regex
        regex pattern("[a-zA-Z0-9. :\\\\]");

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                    else if (event.key.code == sf::Keyboard::Return)
                    {
                        // User pressed Enter, save the board to the chosen location
                        if (!savePath.empty())
                        {
                            promptt = readBoardFromFile(savePath);
                            window.close();
                        }
                    }
                }
                else if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b' && !savePath.empty())
                    {
                        // Backspace key pressed, remove last character from savePath
                        savePath.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        // User entered a printable ASCII character, append it to the save path
                        char enteredChar = static_cast<char>(event.text.unicode);
                        string enteredStr(1, enteredChar);

                        // Check if the entered character matches the regex pattern
                        if (regex_match(enteredStr, pattern))
                        {
                            savePath += enteredStr;
                        }
                    }
                }
            }

            window.clear(sf::Color(109, 109, 110, 255));

            sf::Text text("Choose save location:", font, 30);
            text.setPosition(50.f, 50.f);
            window.draw(text);
            // Display the selected save path
            string displayPath = savePath.empty() ? "No path selected" : savePath;
            sf::Text savePathText(displayPath, font, 20);
            savePathText.setPosition(50.f, 100.f);
            window.draw(savePathText);

            window.display();
        }
        sf::RenderWindow window2(sf::VideoMode(300, 200), "Load Board");
        font.loadFromFile("./Raleway-Regular.ttf");
        while (window2.isOpen())
        {
            sf::Event event;
            while (window2.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window2.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window2.close();
                    }
                    else if (event.key.code == sf::Keyboard::Return)
                    {
                        window2.close();
                    }
                }
            }

            window2.clear(sf::Color(109, 109, 110, 255));
            if (promptt)
            {
                sf::Text text("Wczytano", font, 50);
                text.setPosition(50.f, 50.f);
                window2.draw(text);
            }
            else
            {
                sf::Text text("Nie udalo sie wczytac", font, 25);
                text.setPosition(25.f, 75.f);
                window2.draw(text);
            }
            window2.display();
        }

    }
    void saveToFile()
    {
        sf::RenderWindow window(sf::VideoMode(400, 300), "Save Board");
        string savePath;
        sf::Font font;
        font.loadFromFile("./Raleway-Regular.ttf");
        bool promptt = false;
        // Regular expression pattern for allowed characters
        regex pattern("[a-zA-Z0-9. :\\\\]");

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                    else if (event.key.code == sf::Keyboard::Return)
                    {
                        // User pressed Enter, save the board to the chosen location
                        if (!savePath.empty())
                        {
                            promptt = saveBoardToFile(savePath);
                            window.close();
                        }
                    }
                }
                else if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b' && !savePath.empty())
                    {
                        // Backspace key pressed, remove last character from savePath
                        savePath.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        // User entered a printable ASCII character, append it to the save path
                        char enteredChar = static_cast<char>(event.text.unicode);
                        string enteredStr(1, enteredChar);

                        // Check if the entered character matches the regex pattern
                        if (regex_match(enteredStr, pattern))
                        {
                            savePath += enteredStr;
                        }
                    }
                }
            }

            window.clear(sf::Color(109, 109, 110, 255));

            sf::Text text("Choose save location:", font, 30);
            text.setPosition(50.f, 50.f);
            window.draw(text);
            // Display the selected save path
            string displayPath = savePath.empty() ? "No path selected" : savePath;
            sf::Text savePathText(displayPath, font, 20);
            savePathText.setPosition(50.f, 100.f);
            window.draw(savePathText);

            window.display();
        }
        sf::RenderWindow window2(sf::VideoMode(300, 200), "Save Board");
        font.loadFromFile("./Raleway-Regular.ttf");
        while (window2.isOpen())
        {
            sf::Event event;
            while (window2.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window2.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window2.close();
                    }
                    else if (event.key.code == sf::Keyboard::Return)
                    {
                        window2.close();
                    }
                }
            }

            window2.clear(sf::Color(109, 109, 110, 255));
            if (promptt)
            {
                sf::Text text("Zapisano", font, 50);
                text.setPosition(50.f, 50.f);
                window2.draw(text);
            }
            else
            {
                sf::Text text("Nie udalo sie zapisac", font, 25);
                text.setPosition(25.f, 75.f);
                window2.draw(text);
            }
            window2.display();
        }

    }
    void SetValue(int X, int Y, int val)
    {
        board[X][Y].setValue(val);
    }
    // generowanie nowej planszy
    void generate()
    {
        CountZero = 0;
        generateBoard();
        RemoveNumbers();
        SetingEdit();
        Copy();
    }

    int GetValue(int X,int Y)
    {
        return board[X][Y].getValue();
    }
    int GetValue2(int X, int Y)
    {
        return board2[X][Y].getValue();
    }
    bool GetEditable(int X, int Y)
    {
        return board[X][Y].isEditable();
    }



    

    // sprawdzenie poprawnoœci planszy
    bool isValid(int CoX,int CoY,int value)
    {
        int check = 0;
        if (isValidColumn(board, CoX, CoY, value) != true)
        {
            check += 1;
        }
        if (isValidRow(board, CoX, CoY, value) != true)
        {
            check += 1;
        }
        if (isValidSquare(board, CoX, CoY, value) != true)
        {
            check += 1;
        }
        if (check > 0)
        {
            return false;
        }
        if (check == 0)
        {
            return true;
        }
    }

    // wyœwietlenie planszy na ekranie
    

private:
    int m = 9;
    // wektor dwuwymiarowy przechowuj¹cy komórki planszy
    vector<vector<Cell>> board; 
    vector<vector<Cell>> board2;
    // wektor przechowuj¹cy dozwolone wartoœci dla komórek planszy
    vector<int> values; 
    
    //licznik zer na planszy po generacji
    int CountZero = 0;

    //liczba pustych pól na planszy
    #define MID 35

    // generowanie wektora dozwolonych wartoœci
    void generateValues() 
    {
        for (int i = 1; i < 10; i++)
        {
            values.push_back(i);
        }
    }
    void Copy()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                board2[i][j].setValue(board[i][j].getValue());
                board2[i][j].setEditable(board[i][j].isEditable());
            }
        }
    }
    // generowanie planszy
    void generateBoard()
    {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j].setValue(0);
                board[i][j].setEditable(true);
            }
            
        }
        auto FirstSubGrid = [](vector<vector<Cell>>& board, int COordinates) {
            
            vector<int> values = { 1,2,3,4,5,6,7,8,9 };
            int end = COordinates + 3;
            int temp;
            
            random_device dev;
            mt19937 rng(dev());
            shuffle(values.begin(), values.end(), rng);
            for (int ver = COordinates; ver < end; ver++)
            {
                for (int hor = COordinates; hor < end; hor++)
                {
                    uniform_int_distribution<mt19937::result_type> dist6(0, (values.size() - 1));
                    temp = dist6(rng);
                    board[ver][hor] = Cell(values[temp], false);
                    values.erase(values.begin() + temp);
                }
            }
        };

        auto FillSubGrid = [&](vector<vector<Cell>>& board, int CoX, int CoY) {
            vector<int> values = { 1,2,3,4,5,6,7,8,9 };
            int endX = CoX + 3;
            int endY = CoY + 3;
            random_device dev;
            mt19937 rng(dev());
            for (int ver = CoX; ver < endX; ver++) {
                for (int hor = CoY; hor < endY; hor++) {
                    shuffle(values.begin(), values.end(), rng);
                    for (int i = 0; i < values.size(); i++) {
                        int value = values[i];
                        if (isValidRow(board, ver, hor, value) && isValidColumn(board, ver, hor, value) && isValidSquare(board, ver, hor, value)) {
                            board[ver][hor].setValue(value);
                            values.erase(values.begin() + i);
                            break;
                        }
                    }
                }
            }
        };

        generateValues();

        //Wype³nienie kwadratów planszy po skosie
        thread FirstSquare(FirstSubGrid, ref(board), 0);
        thread MiddleSquare(FirstSubGrid, ref(board), 3);
        thread BottomRightSquare(FirstSubGrid, ref(board), 6);

        FirstSquare.join();
        MiddleSquare.join();
        BottomRightSquare.join();

        //Wype³nienie prawego górnego rogu oraz lewego dolnego rogu
        thread CornerSquare(FillSubGrid, ref(board), 0, 6);
        thread SCornerSquare(FillSubGrid, ref(board), 6, 0);

        CornerSquare.join();
        SCornerSquare.join();

        //Wype³nienie œrodkowego kwadratu z góry oraz z lewej
        thread TopSquare(FillSubGrid, ref(board), 0, 3);
        thread LeftSquare(FillSubGrid, ref(board), 3, 0);

        TopSquare.join();
        LeftSquare.join();
        

        //wype³nienie dolnego oraz prawego kwadratu
        
        thread BottomSquare(FillSubGrid, ref(board), 6, 3);
        thread RightSquare(FillSubGrid, ref(board), 3, 6);

        BottomSquare.join();
        RightSquare.join();

    }


    //Tworzenie queue koordynatów na planszy
    queue<pair<int, int>>get_cord_queue()
    {
        random_device dev;
        mt19937 rng(dev());

        deque<pair<int, int>> que;
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                pair <int, int> cord(i, j);
                que.push_back(cord);
            }
        }
        //Shuffles the deque, constructs a normal queue, and returns it.
        shuffle(que.begin(), que.end(),rng);
        queue<pair<int, int>> art(que);
        return art;
    }



    //Usuwanie okreœlonej liczby numerów z planszy aby zrobiæ gotow¹ do rozwi¹zania plansze.
    void RemoveNumbers()
    {

        auto cor = get_cord_queue();
        int counter = MID - CountZero;

        while (counter != 0 && !cor.empty()) {
            pair<int, int> element = cor.front();

            if (board[element.first][element.second].getValue() != 0)
            {
                board[element.first][element.second].setValue(0);
                board[element.first][element.second].setEditable(true);
                counter--;
            }

            cor.pop();
        }

    }


    void SetingEdit()
    {
        for (int ver = 0; ver < 9; ver++)
        {
            for (int hor = 0; hor < 9; hor++)
            {
                if (board[ver][hor].getValue() != 0)
                {
                    board[ver][hor].setEditable(false);
                }
                else
                {
                    board[ver][hor].setEditable(true);
                }
            }
        }
    }

    // sprawdzenie poprawnoœci wiersza
    bool isValidRow(vector<vector<Cell>> board,int CoX,int CoY,int value)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[CoX][i].getValue() == value && i !=CoY)
            {
                return false;
            }
        }
        return true;
    }
    // sprawdzenie poprawnoœci kolumny
    bool isValidColumn(vector<vector<Cell>> board, int CoX,int CoY, int value)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[i][CoY].getValue() == value && i != CoX)
            {
                return false;
            }
        }
        return true;
    }
    // sprawdzenie poprawnoœci kwadratu
    bool isValidSquare(vector<vector<Cell>> board,int CoX, int CoY,int value )
    {
        int r = CoX - CoX % 3;
        int c = CoY - CoY % 3;
        for (int i = r; i < (r + 3); i++)
        {
            
            for (int j = c; j < (c + 3); j++)
            {
                if (board[i][j].getValue() == value && (i != CoX || j != CoY))
                {
                    return false;
                }
                
            }
        }
        return true;
    }
    bool saveBoardToFile(const filesystem::path& filePath) {
        string pathString = filePath.generic_string();
        replace(pathString.begin(), pathString.end(), '/', '\\');
        filesystem::path Path = pathString;
        ofstream file(Path);
        if (file.is_open()) {
            for (const auto& row : board) {
                ranges::for_each(row, [&](const Cell& cell) {
                    file << cell.getValue() << ' ';
                    });
                file << '\n';
            }
            file << '\n';
            for (const auto& row : board) {
                ranges::for_each(row, [&](const Cell& cell) {
                    file << cell.isEditable() << ' ';
                    });
                file << '\n';
            }
            file.close();
            return true;

        }
        else {
            return false;
        }
    }
    bool readBoardFromFile(const string& filename) 
    {
        ifstream file(filename);
        string line;
        bool isEditableSection = false;
        int i = 0;
        if (!file.is_open()) {
            return false;
        }

        while (getline(file, line)) 
        {

            if (line.empty()) {
                isEditableSection = true;
                continue;
            }
            //ranges
            auto filtered = line | views::filter([](char c) { return c != ' '; });

            string result;
            
            
            for (char c : filtered) {
                result.push_back(c);
            }

            if (!isEditableSection)
            {
                for (int j = 0; j < 9; j++)
                {
                    char c = result[j];
                    string singleCharString(1, c);
                    board[i][j].setValue(stoi(singleCharString));
                    board2[i][j].setValue(stoi(singleCharString));
                }
                if (i >= 8)
                {
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                for (int j = 0; j < 9; j++)
                {
                    char c = result[j];
                    string singleCharString(1, c);
                    board[i][j].setEditable(stoi(singleCharString));
                    board2[i][j].setEditable(stoi(singleCharString));

                }
                    i++;
                
            }
            
        }

        return true;
    }
};