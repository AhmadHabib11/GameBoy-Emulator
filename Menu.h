#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Screen.h"
#include "InputSystem.h"
#include "GameBoy.h" 
#include "SoundSystem.h"
#include <SFML/Audio.hpp>


#include "SnakeGame.h"
#include "HangmanGame.h"
#include "WordleGame.h"


using namespace std;


class Menu {
private:
    std::string menuOptions[3] = { "Game  Library", "Settings", "Exit" };
    std::string gameLibraryOptions[3] = { "SnakeGame", "HangmanGame", "WordleGame" };
    int selectedIndex = 0;
    int gameLibraryIndex = 0;
    sf::Texture gameboyTexture;
    sf::Sprite gameboySprite;
    sf::RenderWindow* window;
    std::string selectedGame; 
    sf::Music backgroundMusic; 
    sf::SoundBuffer startSoundBuffer;
    sf::Sound startSound;

	bool isMainMenu;           // flag for main menu state
	bool isNameEntered = false; // flag for checking if name is entered

public:
    Menu() : window(nullptr), selectedGame("") {
        if (!gameboyTexture.loadFromFile("game-boy-clipart-lg.png")) {
            cout << "Failed to load GameBoy texture!" << std::endl;
        }
        gameboySprite.setTexture(gameboyTexture);
        float scaleX = 1200.f / gameboyTexture.getSize().x;
        float scaleY = 800.f / gameboyTexture.getSize().y;
        gameboySprite.setScale(scaleX, scaleY);

       
        if (!startSoundBuffer.loadFromFile("C:/Users/ahmed_nxwp15x/Desktop/OOPProject/oopproject/startsound.wav")) {
            cout << "Failed to load GameBoy start sound!" << std::endl;
        }
        startSound.setBuffer(startSoundBuffer);
    }

void displaySplashScreen(Screen& screen) {
    window = &screen.getWindow();
    sf::Font retroFont;
    if (!retroFont.loadFromFile("ARCADECLASSIC.ttf")) {
        cout << "Failed to load retro font!" << std::endl;
        return;
    }

    sf::Font lilitaFont;
    if (!lilitaFont.loadFromFile("LilitaOne-Regular.ttf")) {
        cout << "Failed to load Lilita One Regular font!" << std::endl;
        return;
    }

    sf::Text titleText;
    titleText.setFont(retroFont);
    titleText.setString("GAMEBOY");
    titleText.setCharacterSize(125);
    titleText.setFillColor(sf::Color(50, 50, 50));
    titleText.setPosition(355, 150);

    sf::Text nameText;
    nameText.setFont(lilitaFont);
    nameText.setString("Ahmad Habib 23i-0011\nAbdullah Rasheed 23i-0646");
    nameText.setCharacterSize(25);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(60.f, 695.f);

   
    sf::Text promptText;
    promptText.setFont(retroFont);
    promptText.setString("Enter your name: ");
    promptText.setCharacterSize(30);
    promptText.setFillColor(sf::Color(50, 50, 50));
    promptText.setPosition(355.f, 150.f);

    sf::Text inputText;
    inputText.setFont(retroFont);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color(50,50,50));
    inputText.setPosition(355.f, 200.f);

    sf::Clock clock; // clock for timing
    std::string playerName; // string to hold the player name
    bool isNamePromptVisible = false; // flag to show name prompt
    bool musicStarted = false; // flag to ensure music plays only once

    
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("C:/Users/ahmed_nxwp15x/Desktop/OOPProject/oopproject/8bit-music-for-game-68698.wav")) {
        cout << "Failed to load background music!" << std::endl;
    }

   
    startSound.play();

    // loop for splash screen interaction
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // handle text input for name
            if (isNamePromptVisible && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13) {  
                   
                   
                   
                    backgroundMusic.stop();

                    displayMainMenu();
                    return;
                }
                else if (event.text.unicode == 8 && !playerName.empty()) {  
                    playerName.pop_back();
                }
                else if (event.text.unicode < 128) {  
                    playerName += static_cast<char>(event.text.unicode);
                }
            }
        }

        // after 6 seconds, show name prompt
        if (clock.getElapsedTime().asSeconds() > 6.0f) {
            isNamePromptVisible = true;

            // start background music if not already started
            if (!musicStarted) {
                backgroundMusic.setLoop(true);
                backgroundMusic.play();
                musicStarted = true;  
            }
        }

        window->clear();


        window->draw(gameboySprite);
        if (!isNamePromptVisible) {
            window->draw(titleText);
            window->draw(nameText);
        }
        else {
            window->draw(promptText);
            inputText.setString(playerName);  
            window->draw(inputText);
        }

        window->display();
    }
}



    void displayMainMenu() {
        isMainMenu = true;  
        sf::Font retroFont;
        retroFont.loadFromFile("ARCADECLASSIC.ttf");

        sf::Text menuText[3];
        for (int i = 0; i < 3; i++) {
            menuText[i].setFont(retroFont);
            menuText[i].setString(menuOptions[i]);
            menuText[i].setCharacterSize(80);
            menuText[i].setFillColor(sf::Color(50, 50, 50));
            menuText[i].setPosition(350, 125 + i * 50);
        }
        menuText[selectedIndex].setFillColor(sf::Color::Red);


        sf::Font lilitaFont;
        lilitaFont.loadFromFile("LilitaOne-Regular.ttf");
        sf::Text nameText;
        nameText.setFont(lilitaFont);
        nameText.setString("Ahmad Habib 23i-0011\nAbdullah Rasheed 23i-0646");
        nameText.setCharacterSize(25);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(60.f, 695.f);




        while (window->isOpen() && isMainMenu) { 
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                InputSystem::handleMenuNavigation(event, selectedIndex, menuText, 3);

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                  
                    navigate(menuOptions[selectedIndex]);
                    
                }
            }

            window->clear();
            window->draw(gameboySprite);
            for (int i = 0; i < 3; i++) {
                window->draw(menuText[i]);
            }
            window->draw(nameText);
            window->display();

        }
    }

    void navigate(const std::string& option) {
        isMainMenu = false;  
      
        if (option == "Game  Library") {
           
            showGameLibraryMenu();
          
        }
        else if (option == "Settings") {
            showSettingsMenu();
        }
        else if (option == "Exit") {
            exit();
        }
    }

    void showGameLibraryMenu() {
        
        isMainMenu = false;  
        sf::Font retroFont;
        retroFont.loadFromFile("ARCADECLASSIC.ttf");
        backgroundMusic.stop();

        sf::Text gameMenuText[3];
        for (int i = 0; i < 3; i++) {
            gameMenuText[i].setFont(retroFont);
            gameMenuText[i].setString(gameLibraryOptions[i]);
            gameMenuText[i].setCharacterSize(80);
            gameMenuText[i].setFillColor(sf::Color(50, 50, 50));
            gameMenuText[i].setPosition(350, 125 + i * 50);
        }
        gameMenuText[gameLibraryIndex].setFillColor(sf::Color::Red);


        sf::Font lilitaFont;
        lilitaFont.loadFromFile("LilitaOne-Regular.ttf");
        sf::Text nameText;
        nameText.setFont(lilitaFont);
        nameText.setString("Ahmad Habib 23i-0011\nAbdullah Rasheed 23i-0646");
        nameText.setCharacterSize(25);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(60.f, 695.f);



        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                InputSystem::handleMenuNavigation(event, gameLibraryIndex, gameMenuText, 3);

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    selectedGame = gameLibraryOptions[gameLibraryIndex];
                    switchGame(selectedGame);
                    return; 
                }
            }

            window->clear();
            window->draw(gameboySprite);
            for (int i = 0; i < 3; i++) {
                window->draw(gameMenuText[i]);
            }
            window->draw(nameText);
            window->display();
        }
    }


    void showSettingsMenu() {
        isMainMenu = false;  
        sf::Font retroFont;
        retroFont.loadFromFile("ARCADECLASSIC.ttf");

        
        string settingsOptions[3] = { "Brightness", "Sound", "Back" };
        sf::Text settingsMenuText[3];

        
        int settingsIndex = 0;  

        
        for (int i = 0; i < 3; i++) {
            settingsMenuText[i].setFont(retroFont);
            settingsMenuText[i].setString(settingsOptions[i]);
            settingsMenuText[i].setCharacterSize(80);
            settingsMenuText[i].setFillColor(sf::Color(50, 50, 50));  
            settingsMenuText[i].setPosition(350, 125 + i * 50);    
        }

        
        settingsMenuText[settingsIndex].setFillColor(sf::Color::Red);

        
        sf::Font lilitaFont;
        lilitaFont.loadFromFile("LilitaOne-Regular.ttf");
        sf::Text nameText;
        nameText.setFont(lilitaFont);
        nameText.setString("Ahmad Habib 23i-0011\nAbdullah Rasheed 23i-0646");
        nameText.setCharacterSize(25);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(60.f, 695.f);

  
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

               
                InputSystem::handleMenuNavigation(event, settingsIndex, settingsMenuText, 3);

            
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    string selectedOption = settingsOptions[settingsIndex];
                    if (selectedOption == "Back") {
                        displayMainMenu();
                        
                        return;
                    }
                    
                    cout << "Selected: " << selectedOption << std::endl;
                }
            }

            window->clear();
            window->draw(gameboySprite);  

            
            for (int i = 0; i < 3; i++) {
                window->draw(settingsMenuText[i]);
            }

           
            window->draw(nameText);

           
            window->display();
        }
    }

    void switchGame(const string& gameName) {
        
        if (gameName == "SnakeGame") {
            SnakeGame snakeGame;
      
            snakeGame.run();  
            
        }
        else if (gameName == "HangmanGame") {
            HangmanGame hangmanGame;
      
            hangmanGame.run(); 
        
        }
        else if (gameName == "WordleGame") {
            WordleGame wordleGame;
         
            wordleGame.run();  
       
        }

       
        if (backgroundMusic.getStatus() != sf::Music::Playing) {
            backgroundMusic.play();
        }
        isMainMenu = true;  
        displayMainMenu(); 
    }

    string getSelectedGame() const {
        return selectedGame;  
    }

    void transition(const string& nextState) {
        cout << "Transitioning to: " << nextState << endl;
    }

    void exit() {
        cout << "Exiting the application..." << endl;
        if (window) {
            window->close();
        }
        backgroundMusic.stop();  
    }
};



