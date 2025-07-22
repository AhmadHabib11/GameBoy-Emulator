#pragma once
#include "Game.h"
#include "Letter.h"
#include "Keyboard.h"
#include "WordDictionary.h"
#include "WordleMenu.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class WordleGame : public Game {
private:
    Letter letterGrid[5][5];
    Keyboard virtualKeyboard;
    WordDictionary wordDictionary;
    WordleMenu wordleMenu;

    sf::Font font;
    sf::Text gameOverText;
    sf::Text feedbackText;
    sf::Text congratsText;
    sf::Clock feedbackClock;

    string currentGuess;
    bool wordGuessed[5];  // tracks if a word has been guessed correctly
    int currentRow;  // keeps track of which row we're at
    bool allWordsGuessed;  // true if all words are guessed
    bool isPaused;  // true if the game is paused
    bool gameOver = false;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Clock highlightClock;

public:
    WordleGame() : virtualKeyboard(font), currentRow(0), allWordsGuessed(false), isPaused(false) {
        if (!font.loadFromFile("LilitaOne-Regular.ttf")) {
            cout << "Error loading font\n";
        }

        if (!backgroundTexture.loadFromFile("1234.jpg")) {
            cout << "Error loading background image\n";
        }
        else {
            backgroundSprite.setTexture(backgroundTexture);
            backgroundSprite.setScale(0.5f, 0.5f); // scale the background to fit the screen
        }


        feedbackText.setFont(font);
        feedbackText.setString("");
        feedbackText.setCharacterSize(36);
        feedbackText.setFillColor(sf::Color::Red);
        feedbackText.setOutlineColor(sf::Color::Black);
        feedbackText.setOutlineThickness(2.f);
        feedbackText.setPosition(580.f, 90.f);

        congratsText.setFont(font);
        congratsText.setString("CONGRATS");
        congratsText.setCharacterSize(45);
        congratsText.setFillColor(sf::Color::Green);
        congratsText.setOutlineColor(sf::Color::Black);
        congratsText.setOutlineThickness(3.f);
        congratsText.setPosition(570.f, 200.f);

        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER\nPRESS ESC\nTO EXIT\nTHE GAME");
        gameOverText.setCharacterSize(40);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setOutlineColor(sf::Color::Black);
        gameOverText.setOutlineThickness(3.f);
        gameOverText.setPosition(570.f, 200.f);




        for (int i = 0; i < 5; i++) {
            wordGuessed[i] = false;
        }

        // set the starting positions for letters
        float startX = 250.f, startY = 100.f;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                letterGrid[row][col] = Letter(startX + col * 60.f, startY + row * 60.f);
            }
        }

        virtualKeyboard.setPosition(250.f, startY + 5 * 60.f + 20.f); // place the keyboard below the grid
    }

    // simple length function for strings
    int getStringLength(const string& str) {
        int length = 0;
        for (char c : str) {
            ++length;
        }
        return length;
    }

    // checks if the string is empty
    bool isStringEmpty(const string& str) {
        return getStringLength(str) == 0;
    }

    // clears the current guess
    void clearString(string& str) {
        str = "";
    }

    // removes the last character from the string
    void removeLastChar(string& str) {
        if (!isStringEmpty(str)) {
            str = str.substr(0, getStringLength(str) - 1);
        }
    }

    void resetGame() {
        clearString(currentGuess);
    }


    void markWordAsGuessed(const string& guessedWord) {
        for (int i = 0; i < 5; i++) {
            if (guessedWord == wordDictionary.getChosenWords()[i] && !wordGuessed[i]) {
                // mark the boxes green if the word is guessed
                for (int j = 0; j < 5; j++) {
                    letterGrid[currentRow][j].boxColor = sf::Color::Green;
                }
                wordGuessed[i] = true;
                break;
            }
        }

        // check if all words are guessed
        allWordsGuessed = true;
        for (int i = 0; i < 5; i++) {
            if (!wordGuessed[i]) {
                allWordsGuessed = false;
                break;
            }
        }

        if (!allWordsGuessed) {
            currentRow++; // move to the next row if not all words are guessed
        }
    }

    // provides feedback for incorrect guesses
    void colorBoxesForIncorrectGuess(const string& guess, const string* chosenWords) {

        bool usedInExactPosition[5][5] = { false };
        bool usedInOtherPosition[5][5] = { false };

        // first mark exact matches as green
        for (int wordIndex = 0; wordIndex < 5; ++wordIndex) {
            for (int col = 0; col < 5; ++col) {
                if (guess[col] == chosenWords[wordIndex][col]) {
                    letterGrid[currentRow][col].boxColor = sf::Color::Green;
                    usedInExactPosition[wordIndex][col] = true;
                    break;
                }
            }
        }

        // then mark misplaced letters as yellow
        for (int col = 0; col < 5; ++col) {
            if (letterGrid[currentRow][col].boxColor == sf::Color::Green) {
                continue;
            }

            bool foundInOtherPosition = false;
            for (int wordIndex = 0; wordIndex < 5; ++wordIndex) {
                for (int letterIndex = 0; letterIndex < 5; ++letterIndex) {
                    if (!usedInExactPosition[wordIndex][letterIndex] &&
                        !usedInOtherPosition[wordIndex][letterIndex] &&
                        guess[col] == chosenWords[wordIndex][letterIndex]) {
                        letterGrid[currentRow][col].boxColor = sf::Color::Yellow;
                        usedInOtherPosition[wordIndex][letterIndex] = true;
                        foundInOtherPosition = true;
                        break;
                    }
                }
                if (foundInOtherPosition) break;
            }

            // if not found, mark as red
            if (!foundInOtherPosition) {
                letterGrid[currentRow][col].boxColor = sf::Color::Red;
            }
        }
    }


    void handleInput(char input) {
        if (isPaused || gameOver) {
            return; // don't process input if the game is paused or over
        }

        if (input >= 'a' && input <= 'z')
            input -= 32;

        if (input >= 'A' && input <= 'Z') {
            if (getStringLength(currentGuess) < 5) {
                currentGuess += input;
                letterGrid[currentRow][getStringLength(currentGuess) - 1].setCharacter(input, font);
            }
        }
        // handle backspace
        if (input == '\b' && !isStringEmpty(currentGuess)) {
            letterGrid[currentRow][getStringLength(currentGuess) - 1].setCharacter(' ', font);
            removeLastChar(currentGuess);
        }
        // handle enter
        if ((input == '\r' || input == '\n') && getStringLength(currentGuess) == 5) {
            bool wordExists = false;
            bool alreadyGuessed = false;
            const string* chosenWords = wordDictionary.getChosenWords();

            // check if word exists in dictionary
            for (int i = 0; i < 5; i++) {
                if (currentGuess == chosenWords[i]) {
                    wordExists = true;
                    break;
                }
            }

            // check if word has already been guessed
            for (int i = 0; i < 5; i++) {
                if (currentGuess == wordDictionary.getChosenWords()[i] && wordGuessed[i]) {
                    alreadyGuessed = true;
                    break;
                }
            }

            // game over if all rows are filled and not all words are guessed
            if (currentRow >= 5 && !allWordsGuessed) {
                gameOver = true;
                return;
            }


            if (alreadyGuessed) {
                feedbackText.setString("ALREADY\nGUESSED");
                feedbackText.setFillColor(sf::Color::Yellow);
                feedbackClock.restart();
                /*clearRow(currentRow);*/
            }
            else if (wordExists) {
                cout << "Correct guess: " << currentGuess << endl;
                markWordAsGuessed(currentGuess);
                feedbackText.setString("");
            }
            else {
                cout << "Incorrect guess! Providing feedback." << endl;
                feedbackText.setString("INCORRECT\n     GUESS");
                feedbackText.setFillColor(sf::Color::Red);
                feedbackClock.restart();
                colorBoxesForIncorrectGuess(currentGuess, chosenWords);
                currentRow++;
            }
            resetGame();
        }
    }







    void handleMouseClick(sf::Vector2i mousePos) {
        if (isPaused) {
            return; // don't process clicks if game is paused
        }

        // don't process clicks if game is paused
        for (int i = 0; i < 26; i++) {
            if (virtualKeyboard.keys[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                char clickedLetter = static_cast<char>('A' + i);
                if (getStringLength(currentGuess) < 5) {
                    currentGuess += clickedLetter; // add clicked letter to guess
                    letterGrid[currentRow][getStringLength(currentGuess) - 1].setCharacter(clickedLetter, font);
                }
                virtualKeyboard.highlightKey(i, true);
                highlightClock.restart();
                break;
            }
        }

        if (isPaused || gameOver) {
            return;
        }



        if (virtualKeyboard.keys[26].getGlobalBounds().contains(mousePos.x, mousePos.y) && getStringLength(currentGuess) == 5) {
            bool wordExists = false;
            bool alreadyGuessed = false;
            const string* chosenWords = wordDictionary.getChosenWords();

            for (int i = 0; i < 5; i++) {
                if (currentGuess == chosenWords[i]) {
                    wordExists = true;
                    break;
                }
            }


            for (int i = 0; i < 5; i++) {
                if (currentGuess == wordDictionary.getChosenWords()[i] && wordGuessed[i]) {
                    alreadyGuessed = true;
                    break;
                }
            }

            if (alreadyGuessed) {
                feedbackText.setString("ALREADY\nGUESSED");
                feedbackText.setFillColor(sf::Color::Yellow);
                feedbackClock.restart();
                /*clearRow(currentRow);*/
            }
            else if (wordExists) {
                cout << "Correct guess: " << currentGuess << endl;
                markWordAsGuessed(currentGuess);
                feedbackText.setString("");
            }
            else {
                cout << "Incorrect guess! Providing feedback." << endl;
                feedbackText.setString("INCORRECT\n     GUESS");
                feedbackText.setFillColor(sf::Color::Red);
                feedbackClock.restart();
                colorBoxesForIncorrectGuess(currentGuess, chosenWords);
                currentRow++;
            }
            resetGame();
            virtualKeyboard.highlightKey(26, true);
            highlightClock.restart();
        }
    }



    void draw(sf::RenderWindow& window) {
        window.draw(backgroundSprite);

        // draw the letter grid
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                letterGrid[row][col].draw(window);
            }
        }

        virtualKeyboard.draw(window);


        window.draw(feedbackText);

        // display congratulations or game over screen
        if (allWordsGuessed) {
            window.draw(congratsText);
        }

        else if (currentRow >= 5) {
            window.draw(gameOverText);
        }


        if (isPaused) {
            // display pause overlay if paused
            sf::RectangleShape pauseOverlay(sf::Vector2f(window.getSize().x, window.getSize().y));
            pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(pauseOverlay);


            sf::Text pauseText;
            pauseText.setFont(font);
            pauseText.setString("    GAME PAUSED....\n  Press R to Resume");
            pauseText.setCharacterSize(48);
            pauseText.setFillColor(sf::Color::Yellow);
            pauseText.setOutlineColor(sf::Color::Black);
            pauseText.setOutlineThickness(3.f);
            pauseText.setPosition(200.f, 250.f);
            window.draw(pauseText);
        }
    }



    void update() {
        if (isPaused || gameOver) {
            return;
        }

        if (highlightClock.getElapsedTime().asSeconds() > 0.1f) {

            for (int i = 0; i < 27; ++i) {
                virtualKeyboard.highlightKey(i, false);
            }
        }


        if (feedbackClock.getElapsedTime().asSeconds() > 0.5f) {
            feedbackText.setString("");
        }
    }

    void run() override {
        // show the menu and start the game if chosen
        bool startGame = wordleMenu.displayMenu();

        if (startGame) {

            sf::RenderWindow window(sf::VideoMode(800, 600), "Wordle Game");

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    // pause/resume handling
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::P) {
                            isPaused = !isPaused;
                        }

                        if (event.key.code == sf::Keyboard::R) {
                            isPaused = false;
                        }


                        if (isPaused) {
                            continue; // don't process other key presses while paused
                        }
                    }


                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::BackSpace) {

                            if (!isStringEmpty(currentGuess)) {
                                removeLastChar(currentGuess);
                                letterGrid[currentRow][getStringLength(currentGuess)].setCharacter(' ', font);
                            }
                        }

                        if (currentRow >= 5 && !allWordsGuessed) {

                            if (event.key.code == sf::Keyboard::Escape) {
                                window.close();
                            }
                            continue;
                        }

                        // close game if all words are guessed and escape is pressed
                        if (event.key.code == sf::Keyboard::Escape && allWordsGuessed) {
                            window.close();
                        }
                    }

                    if (event.type == sf::Event::MouseButtonPressed && !allWordsGuessed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            handleMouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                        }
                    }
                }

                window.clear(sf::Color::White);
                update();
                draw(window);


                if (allWordsGuessed) {
                    window.draw(congratsText);

                }


                else if (currentRow >= 5) {
                    window.draw(gameOverText);

                }


                window.display();
            }

            if (allWordsGuessed) {
                cout << "Congrats you guessed all the words correctly..." << endl;
            }
            else if (currentRow >= 5) {
                cout << "Game over..." << endl;
            }
        }
        else {

            cout << "Exiting the game..." << endl;
        }
    }



};


