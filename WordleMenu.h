#pragma once

#include "WordleGame.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class WordleMenu {
private:
    sf::RenderWindow menuWindow;
    sf::Font font;
    sf::Text startText;
    sf::Text exitText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    int selectedOption; // 0 = start game, 1 = exit

    

public:
	// sets up the window, font, background, and text
	void initializeGraphics() {
		menuWindow.create(sf::VideoMode(800, 600), "Wordle Menu");

		if (!font.loadFromFile("LilitaOne-Regular.ttf")) {
			cout << "Error loading font!" << endl;
		}

		if (!backgroundTexture.loadFromFile("wordlebg.png")) {
			cout << "Error loading background image!" << endl;
		}

		// fit the background image to the window size
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setScale(
			static_cast<float>(menuWindow.getSize().x) / backgroundTexture.getSize().x,
			static_cast<float>(menuWindow.getSize().y) / backgroundTexture.getSize().y
		);

		// configure "START GAME" text
		startText.setFont(font);
		startText.setCharacterSize(40);
		startText.setFillColor(sf::Color::Green);
		startText.setOutlineColor(sf::Color::Black);
		startText.setOutlineThickness(2.f);
		startText.setString("START GAME");
		startText.setPosition(300.f, 120.f);

		// configure "EXIT" text
		exitText.setFont(font);
		exitText.setCharacterSize(40);
		exitText.setFillColor(sf::Color::White);
		exitText.setOutlineColor(sf::Color::Black);
		exitText.setOutlineThickness(2.f);
		exitText.setString("EXIT");
		exitText.setPosition(355.f, 420.f);

		selectedOption = 0; // default to start game
	}

	// updates which option is highlighted based on selectedOption
	void updateMenuColors() {
		if (selectedOption == 0) {
			startText.setFillColor(sf::Color::Green);
			exitText.setFillColor(sf::Color::White);
		}
		else if (selectedOption == 1) {
			startText.setFillColor(sf::Color::White);
			exitText.setFillColor(sf::Color::Red);
		}
	}
    // main loop for displaying the menu and handling input
    bool displayMenu() {
        initializeGraphics();

        while (menuWindow.isOpen()) {
            sf::Event event;
            while (menuWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) { // close the menu if the window is closed
                    menuWindow.close();
                    return false;
                }
                // for hovering up and down on menu
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) { // move selection up
                        selectedOption = (selectedOption - 1 + 2) % 2; // wrap around
                        updateMenuColors();
                    }
                    if (event.key.code == sf::Keyboard::Down) { // move selection down
                        selectedOption = (selectedOption + 1) % 2; // wrap around
                        updateMenuColors();
                    }
                    if (event.key.code == sf::Keyboard::Enter) { // confirm selection
                        menuWindow.close();
                        return selectedOption == 0; // true if start game, false if exit
                    }
                }
            }

            // draw everything
            menuWindow.clear();
            menuWindow.draw(backgroundSprite);
            menuWindow.draw(startText);
            menuWindow.draw(exitText);
            menuWindow.display();
        }
        return false;
    }
};
