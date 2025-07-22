#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;


class HangmanMenu {
private:
	sf::RenderWindow menuWindow;
	sf::Font font;
	sf::Text titleText;
	sf::Text startText;
	sf::Text exitText;
	sf::Texture backgroundTexture; 
	sf::Sprite backgroundSprite;   
	int selectedOption; 


	

public:
	void initializeGraphics() {
		menuWindow.create(sf::VideoMode(800, 600), "Hangman Menu");

		if (!font.loadFromFile("LilitaOne-Regular.ttf")) {
			cout << "Error loading font!" << endl;
		}

		if (!backgroundTexture.loadFromFile("hangmanbg.jpg")) {
			cout << "Error loading background image!" << endl;
		}


		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setScale(
			static_cast<float>(menuWindow.getSize().x) / backgroundTexture.getSize().x,
			static_cast<float>(menuWindow.getSize().y) / backgroundTexture.getSize().y
		);


		titleText.setFont(font);
		titleText.setCharacterSize(50);
		titleText.setFillColor(sf::Color::White);
		titleText.setOutlineColor(sf::Color::Black);
		titleText.setOutlineThickness(3.f);
		titleText.setString("HANGMAN GAME");
		titleText.setPosition(230.f, 30.f);


		startText.setFont(font);
		startText.setCharacterSize(35);
		startText.setFillColor(sf::Color::Green); // Default selection
		startText.setOutlineColor(sf::Color::Black);
		startText.setOutlineThickness(2.f);
		startText.setString("START GAME");
		startText.setPosition(320.f, 250.f);


		exitText.setFont(font);
		exitText.setCharacterSize(35);
		exitText.setFillColor(sf::Color::White);
		exitText.setOutlineColor(sf::Color::Black);
		exitText.setOutlineThickness(2.f);
		exitText.setString("EXIT");
		exitText.setPosition(370.f, 350.f);

		selectedOption = 0;
	}


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

	bool displayMenu() {
		initializeGraphics();

		while (menuWindow.isOpen()) {
			sf::Event event;
			while (menuWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					menuWindow.close();
					return false; 
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up) {
						selectedOption = (selectedOption - 1 + 2) % 2; 
						updateMenuColors();
					}
					if (event.key.code == sf::Keyboard::Down) {
						selectedOption = (selectedOption + 1) % 2; 
						updateMenuColors();
					}
					if (event.key.code == sf::Keyboard::Enter) {
						menuWindow.close();
						if (selectedOption == 0) {
							return true; 
						}
						else if (selectedOption == 1) {
							return false; 
						}
					}
				}
			}

			menuWindow.clear();
			menuWindow.draw(backgroundSprite); 
			menuWindow.draw(titleText);
			menuWindow.draw(startText);
			menuWindow.draw(exitText);
			menuWindow.display();
		}
		return false; 
	}
};
